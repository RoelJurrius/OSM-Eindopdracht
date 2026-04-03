#include "cserver.h"
#include "sensor_mock.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST_SIZE 256
#define MAX_METHOD_LEN 8
#define MAX_PATH_LEN 64
#define MAX_VERSION_LEN 16
#define MAX_BODY_LEN 32
#define MAX_SEGMENTS 4
#define MAX_SEGMENT_LEN 16

struct parsed_request {
  bool valid_syntax;
  bool has_content_length;
  int content_length;
  char method[MAX_METHOD_LEN];
  char path[MAX_PATH_LEN];
  char version[MAX_VERSION_LEN];
  char body[MAX_BODY_LEN];
};

static struct response bad_request_response(void);
static struct response not_found_response(void);
static bool read_request_text(struct stream stream,
                              char buffer[], size_t len);
static bool split_request(const char request[],
                          struct parsed_request* parsed);
static bool parse_start_line(char line[],
                             struct parsed_request* parsed);
static bool parse_headers(char headers[],
                          struct parsed_request* parsed);
static bool parse_content_length(const char value[],
                                 int* content_length);
static int
split_path_segments(const char path[],
                    char segments[][MAX_SEGMENT_LEN],
                    int max_segments);
static bool is_integer_text(const char text[]);
static struct response
route_request(const struct parsed_request* parsed);
static struct response
handle_put(const char segments[][MAX_SEGMENT_LEN],
           int segment_count,
           const struct parsed_request* parsed);
static struct response
handle_post(const char segments[][MAX_SEGMENT_LEN],
            int segment_count,
            const struct parsed_request* parsed);
static struct response
handle_delete(const char segments[][MAX_SEGMENT_LEN],
              int segment_count);
static struct response
handle_get(const char segments[][MAX_SEGMENT_LEN],
           int segment_count);

static struct response bad_request_response(void) {
  struct response response = {.code = BAD_REQUEST_400,
                              .get_avg = 0.0};
  return response;
}

static struct response not_found_response(void) {
  struct response response = {.code = NOT_FOUND_404,
                              .get_avg = 0.0};
  return response;
}

static bool read_request_text(struct stream stream,
                              char buffer[], size_t len) {
  size_t index = 0U;

  if (len == 0U) {
    return false;
  }

  while (stream.available() != 0) {
    if (index + 1U >= len) {
      return false;
    }

    buffer[index] = stream.read();
    index++;
  }

  buffer[index] = '\0';
  return true;
}

static bool
parse_start_line(char line[],
                 struct parsed_request* parsed) {
  char extra = '\0';
  int matched =
      sscanf(line, "%7s %63s %15s %c", parsed->method,
             parsed->path, parsed->version, &extra);

  if (matched != 3) {
    return false;
  }

  if (strcmp(parsed->version, "HTTP/1.0") != 0) {
    return false;
  }

  if (parsed->path[0] != '/') {
    return false;
  }

  return true;
}

static bool parse_content_length(const char value[],
                                 int* content_length) {
  long parsed_value;
  char* endptr = NULL;

  if (*value == '\0') {
    return false;
  }

  parsed_value = strtol(value, &endptr, 10);

  if (*endptr != '\0' || parsed_value < 0L ||
      parsed_value > 32767L) {
    return false;
  }

  *content_length = (int)parsed_value;
  return true;
}

static bool parse_headers(char headers[],
                          struct parsed_request* parsed) {
  char* line = strtok(headers, "\r\n");

  parsed->has_content_length = false;
  parsed->content_length = 0;

  while (line != NULL) {
    char* colon = strchr(line, ':');
    char* value;

    if (colon == NULL) {
      return false;
    }

    *colon = '\0';
    value = colon + 1;

    while (*value == ' ') {
      value++;
    }

    if (strcmp(line, "Content-Length") == 0) {
      if (parsed->has_content_length) {
        return false;
      }
      if (!parse_content_length(value,
                                &parsed->content_length)) {
        return false;
      }
      parsed->has_content_length = true;
    }

    line = strtok(NULL, "\r\n");
  }

  return true;
}

static bool split_request(const char request[],
                          struct parsed_request* parsed) {
  char mutable_request[MAX_REQUEST_SIZE];
  char* header_end;
  char* body_start;
  char* first_line_end;
  size_t body_len;
  size_t expected_body_len;

  memset(parsed, 0, sizeof(*parsed));

  if (strlen(request) >= sizeof(mutable_request)) {
    return false;
  }

  strcpy(mutable_request, request);

  header_end = strstr(mutable_request, "\r\n\r\n");
  if (header_end == NULL) {
    return false;
  }

  first_line_end = strstr(mutable_request, "\r\n");
  if (first_line_end == NULL ||
      first_line_end > header_end) {
    return false;
  }

  body_start = header_end + 4;
  body_len = strlen(body_start);
  *header_end = '\0';
  *first_line_end = '\0';
  if (!parse_start_line(mutable_request, parsed)) {
    return false;
  }

  if (!parse_headers(first_line_end + 2, parsed)) {
    return false;
  }

  expected_body_len = (size_t)parsed->content_length;
  if (parsed->has_content_length) {
    if (body_len != expected_body_len) {
      return false;
    }
  } else if (body_len != 0U) {
    return false;
  }

  if (body_len >= sizeof(parsed->body)) {
    return false;
  }

  memcpy(parsed->body, body_start, body_len + 1U);
  parsed->valid_syntax = true;
  return true;
}

static int
split_path_segments(const char path[],
                    char segments[][MAX_SEGMENT_LEN],
                    int max_segments) {
  char copy[MAX_PATH_LEN];
  char* segment;
  int count = 0;

  if (strlen(path) >= sizeof(copy)) {
    return -1;
  }

  strcpy(copy, path);
  segment = strtok(copy, "/");

  while (segment != NULL) {
    size_t segment_len = strlen(segment);

    if (count >= max_segments ||
        segment_len >= (size_t)MAX_SEGMENT_LEN) {
      return -1;
    }

    strcpy(segments[count], segment);
    count++;
    segment = strtok(NULL, "/");
  }

  return count;
}

static bool is_integer_text(const char text[]) {
  size_t i;
  size_t len = strlen(text);

  if (len == 0U) {
    return false;
  }

  for (i = 0U; i < len; i++) {
    if (!isdigit((unsigned char)text[i])) {
      return false;
    }
  }

  return true;
}

static struct response
handle_put(const char segments[][MAX_SEGMENT_LEN],
           int segment_count,
           const struct parsed_request* parsed) {
  struct response response;

  if (segment_count != 2) {
    return not_found_response();
  }

  if (!parsed->has_content_length) {
    return bad_request_response();
  }

  if (strcmp(segments[0], "config") != 0) {
    return not_found_response();
  }

  if (strcmp(segments[1], "mode") == 0) {
    if (strcmp(parsed->body, "active") == 0) {
      sensorsSetActive(true);
      response.code = CREATED_201_PUT_MODE_ACTIVE;
      return response;
    }

    if (strcmp(parsed->body, "passive") == 0) {
      sensorsSetActive(false);
      response.code = CREATED_201_PUT_MODE_PASSIVE;
      return response;
    }

    return bad_request_response();
  }

  if (strcmp(segments[1], "cbuffsize") == 0) {
    long new_size;

    if (!is_integer_text(parsed->body)) {
      return bad_request_response();
    }

    new_size = strtol(parsed->body, NULL, 10);
    if (new_size <= 0L || new_size > 32767L) {
      return bad_request_response();
    }

    if (!sensorsSetBufferSize((size_t)new_size)) {
      return bad_request_response();
    }

    response.code = CREATED_201_PUT_CBUFFSIZE;
    return response;
  }

  return not_found_response();
}

static struct response
handle_post(const char segments[][MAX_SEGMENT_LEN],
            int segment_count,
            const struct parsed_request* parsed) {
  long value;
  int sensor_id;
  struct response response;

  if (segment_count != 2) {
    return not_found_response();
  }

  if (!parsed->has_content_length ||
      strcmp(segments[0], "sensors") != 0) {
    return bad_request_response();
  }

  if (strcmp(segments[1], "1") == 0) {
    sensor_id = SENSORID1;
  } else if (strcmp(segments[1], "2") == 0) {
    sensor_id = SENSORID2;
  } else {
    return not_found_response();
  }

  if (!is_integer_text(parsed->body)) {
    return bad_request_response();
  }

  value = strtol(parsed->body, NULL, 10);
  if (value < 0L || value > 1023L) {
    return bad_request_response();
  }

  if (!sensorAddMeasurement(sensor_id, (int)value)) {
    return bad_request_response();
  }

  response.code = CREATED_201_POST_MEASUREMENT;
  return response;
}

static struct response
handle_delete(const char segments[][MAX_SEGMENT_LEN],
              int segment_count) {
  struct response response;

  if (segment_count != 2) {
    return not_found_response();
  }

  if (strcmp(segments[0], "sensors") != 0) {
    return not_found_response();
  }

  if (strcmp(segments[1], "1") == 0) {
    sensorReset(SENSORID1);
  } else if (strcmp(segments[1], "2") == 0) {
    sensorReset(SENSORID2);
  } else {
    return not_found_response();
  }

  response.code = CREATED_201_DELETE_MEASUREMENTS;
  return response;
}

static struct response
handle_get(const char segments[][MAX_SEGMENT_LEN],
           int segment_count) {
  int sensor_id;
  struct response response;

  if (segment_count != 3) {
    return not_found_response();
  }

  if (strcmp(segments[0], "sensors") != 0) {
    return not_found_response();
  }

  if (strcmp(segments[1], "1") == 0) {
    sensor_id = SENSORID1;
  } else if (strcmp(segments[1], "2") == 0) {
    sensor_id = SENSORID2;
  } else {
    return not_found_response();
  }

  if (strcmp(segments[2], "avg") == 0) {
    response.code = OK_200_GET_AVG;
    if (sensorStatsCount(sensor_id) == 0UL) {
      response.get_avg = -1.0;
    } else {
      response.get_avg = sensorGetAvg(sensor_id);
    }
    return response;
  }

  if (strcmp(segments[2], "stdev") == 0) {
    response.code = OK_200_GET_STDEV;
    if (sensorStatsCount(sensor_id) == 0UL) {
      response.get_stdev = -1.0;
    } else {
      response.get_stdev = sensorGetStdev(sensor_id);
    }
    return response;
  }

  if (strcmp(segments[2], "actual") == 0) {
    response.code = OK_200_GET_ACTUAL;
    if (sensorBufferCount(sensor_id) == 0U) {
      response.get_actual = -1.0;
    } else {
      response.get_actual = sensorGetActual(sensor_id);
    }
    return response;
  }

  return not_found_response();
}

static struct response
route_request(const struct parsed_request* parsed) {
  char segments[MAX_SEGMENTS][MAX_SEGMENT_LEN] = {{0}};
  int segment_count = split_path_segments(
      parsed->path, segments, MAX_SEGMENTS);

  if (segment_count < 0) {
    return bad_request_response();
  }

  if (strcmp(parsed->method, "PUT") == 0) {
    return handle_put(segments, segment_count, parsed);
  }

  if (strcmp(parsed->method, "POST") == 0) {
    return handle_post(segments, segment_count, parsed);
  }

  if (strcmp(parsed->method, "DELETE") == 0) {
    return handle_delete(segments, segment_count);
  }

  if (strcmp(parsed->method, "GET") == 0) {
    if (parsed->has_content_length &&
        parsed->content_length != 0) {
      return bad_request_response();
    }
    return handle_get(segments, segment_count);
  }

  return bad_request_response();
}

struct response handleRequest(struct stream stream) {
  char request_text[MAX_REQUEST_SIZE];
  struct parsed_request parsed;

  if (!read_request_text(stream, request_text,
                         sizeof(request_text))) {
    return bad_request_response();
  }

  if (!split_request(request_text, &parsed) ||
      !parsed.valid_syntax) {
    return bad_request_response();
  }

  return route_request(&parsed);
}

const char* handleResponse(struct stream stream) {
  static char response_text[128];
  struct response response = handleRequest(stream);

  switch (response.code) {
  case OK_200_GET_AVG:
    snprintf(response_text, sizeof(response_text),
             "HTTP/1.0 200 OK\r\n"
             "Connection: close\r\n"
             "\r\n"
             "%.1f",
             response.get_avg);
    break;
  case OK_200_GET_STDEV:
    snprintf(response_text, sizeof(response_text),
             "HTTP/1.0 200 OK\r\n"
             "Connection: close\r\n"
             "\r\n"
             "%.1f",
             response.get_stdev);
    break;
  case OK_200_GET_ACTUAL:
    snprintf(response_text, sizeof(response_text),
             "HTTP/1.0 200 OK\r\n"
             "Connection: close\r\n"
             "\r\n"
             "%.1f",
             response.get_actual);
    break;
  case CREATED_201_PUT_MODE_ACTIVE:
  case CREATED_201_PUT_MODE_PASSIVE:
  case CREATED_201_PUT_CBUFFSIZE:
  case CREATED_201_POST_MEASUREMENT:
  case CREATED_201_DELETE_MEASUREMENTS:
    snprintf(response_text, sizeof(response_text),
             "HTTP/1.0 201 Created\r\n"
             "Connection: close\r\n"
             "\r\n");
    break;
  case NOT_FOUND_404:
    snprintf(response_text, sizeof(response_text),
             "HTTP/1.0 404 Not Found\r\n"
             "Connection: close\r\n"
             "\r\n");
    break;
  case BAD_REQUEST_400:
  default:
    snprintf(response_text, sizeof(response_text),
             "HTTP/1.0 400 Bad Request\r\n"
             "Connection: close\r\n"
             "\r\n");
    break;
  }

  return response_text;
}
