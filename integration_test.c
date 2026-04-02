/* GENERATION SEED:
42
*/

#include "arduino_server/cserver.h"
#include "buffermock.h"
#include <glib.h>
#include <math.h>
#include <stdint.h>

void single_value_1() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_PUT_MODE_PASSIVE);
  }
  {
    reset_buffer("DELETE /sensors/1 HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_DELETE_MEASUREMENTS);
  }
  {
    reset_buffer("\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
10");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_PUT_CBUFFSIZE);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
228");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("GET /sensors/1/avg HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_AVG);
    g_assert_cmpfloat_with_epsilon(received.get_avg, 228.0,
                                   0.1);
  }
  {
    reset_buffer("GET /sensors/1/stdev HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_STDEV);
    g_assert_cmpfloat_with_epsilon(received.get_stdev, 0.0,
                                   0.1);
  }
  {
    reset_buffer("GET /sensors/1/actual HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_ACTUAL);
    g_assert_cmpfloat_with_epsilon(received.get_actual,
                                   228.0, 0.1);
  }
}

void single_value_2() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_PUT_MODE_PASSIVE);
  }
  {
    reset_buffer("DELETE /sensors/2 HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_DELETE_MEASUREMENTS);
  }
  {
    reset_buffer("\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
10");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_PUT_CBUFFSIZE);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
51");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("GET /sensors/2/avg HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_AVG);
    g_assert_cmpfloat_with_epsilon(received.get_avg, 51.0,
                                   0.1);
  }
  {
    reset_buffer("GET /sensors/2/stdev HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_STDEV);
    g_assert_cmpfloat_with_epsilon(received.get_stdev, 0.0,
                                   0.1);
  }
  {
    reset_buffer("GET /sensors/2/actual HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_ACTUAL);
    g_assert_cmpfloat_with_epsilon(received.get_actual,
                                   51.0, 0.1);
  }
}

void multiple_values() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_PUT_MODE_PASSIVE);
  }
  {
    reset_buffer("DELETE /sensors/1 HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_DELETE_MEASUREMENTS);
  }
  {
    reset_buffer("DELETE /sensors/2 HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_DELETE_MEASUREMENTS);
  }
  {
    reset_buffer("\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
14");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_PUT_CBUFFSIZE);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
501");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
457");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
285");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
209");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
178");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
864");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
65");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
61");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
191");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
447");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
476");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
54");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
407");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
859");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("GET /sensors/1/avg HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_AVG);
    g_assert_cmpfloat_with_epsilon(received.get_avg, 361.0,
                                   0.1);
  }
  {
    reset_buffer("GET /sensors/1/stdev HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_STDEV);
    g_assert_cmpfloat_with_epsilon(received.get_stdev,
                                   255.74820206043063, 0.1);
  }
  {
    reset_buffer("GET /sensors/1/actual HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_ACTUAL);
    g_assert_cmpfloat_with_epsilon(received.get_actual,
                                   361.0, 0.1);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
451");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
919");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
569");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
13");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
326");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
865");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
696");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("GET /sensors/2/avg HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_AVG);
    g_assert_cmpfloat_with_epsilon(received.get_avg,
                                   548.4285714285714, 0.1);
  }
  {
    reset_buffer("GET /sensors/2/stdev HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_STDEV);
    g_assert_cmpfloat_with_epsilon(received.get_stdev,
                                   294.0825234729954, 0.1);
  }
  {
    reset_buffer("GET /sensors/2/actual HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_ACTUAL);
    g_assert_cmpfloat_with_epsilon(received.get_actual,
                                   548.4285714285714, 0.1);
  }
}

void cbuff_overflow_1() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_PUT_MODE_PASSIVE);
  }
  {
    reset_buffer("DELETE /sensors/1 HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_DELETE_MEASUREMENTS);
  }
  {
    reset_buffer("\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 1\r\n\
\r\n\
5");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_PUT_CBUFFSIZE);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
318");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
440");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
689");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
209");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
189");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
778");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
198");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("GET /sensors/1/avg HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_AVG);
    g_assert_cmpfloat_with_epsilon(received.get_avg, 403.0,
                                   0.1);
  }
  {
    reset_buffer("GET /sensors/1/stdev HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_STDEV);
    g_assert_cmpfloat_with_epsilon(received.get_stdev,
                                   225.6647323543744, 0.1);
  }
  {
    reset_buffer("GET /sensors/1/actual HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_ACTUAL);
    g_assert_cmpfloat_with_epsilon(received.get_actual,
                                   412.6, 0.1);
  }
}

void cbuff_overflow_2() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_PUT_MODE_PASSIVE);
  }
  {
    reset_buffer("DELETE /sensors/2 HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_DELETE_MEASUREMENTS);
  }
  {
    reset_buffer("\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 1\r\n\
\r\n\
6");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_PUT_CBUFFSIZE);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
704");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
541");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
88");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
940");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
255");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
775");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
161");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
600");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("GET /sensors/2/avg HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_AVG);
    g_assert_cmpfloat_with_epsilon(received.get_avg, 508.0,
                                   0.1);
  }
  {
    reset_buffer("GET /sensors/2/stdev HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_STDEV);
    g_assert_cmpfloat_with_epsilon(received.get_stdev,
                                   288.68235138296905, 0.1);
  }
  {
    reset_buffer("GET /sensors/2/actual HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_ACTUAL);
    g_assert_cmpfloat_with_epsilon(received.get_actual,
                                   469.8333333333333, 0.1);
  }
}

void complete() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_PUT_MODE_PASSIVE);
  }
  {
    reset_buffer("DELETE /sensors/1 HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_DELETE_MEASUREMENTS);
  }
  {
    reset_buffer("DELETE /sensors/2 HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_DELETE_MEASUREMENTS);
  }
  {
    reset_buffer("\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 1\r\n\
\r\n\
4");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_PUT_CBUFFSIZE);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
740");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
393");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
142");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
93");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("GET /sensors/1/avg HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_AVG);
    g_assert_cmpfloat_with_epsilon(received.get_avg, 342.0,
                                   0.1);
  }
  {
    reset_buffer("GET /sensors/1/stdev HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_STDEV);
    g_assert_cmpfloat_with_epsilon(received.get_stdev,
                                   256.4205529983897, 0.1);
  }
  {
    reset_buffer("GET /sensors/1/actual HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_ACTUAL);
    g_assert_cmpfloat_with_epsilon(received.get_actual,
                                   342.0, 0.1);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
466");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
592");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
163");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
476");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
206");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
778");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
569");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("DELETE /sensors/2 HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_DELETE_MEASUREMENTS);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
928");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
747");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
333");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
758");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
727");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
429");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
546");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
146");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
350");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("GET /sensors/2/avg HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_AVG);
    g_assert_cmpfloat_with_epsilon(received.get_avg,
                                   551.5555555555555, 0.1);
  }
  {
    reset_buffer("GET /sensors/2/stdev HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_STDEV);
    g_assert_cmpfloat_with_epsilon(received.get_stdev,
                                   240.65332885991418, 0.1);
  }
  {
    reset_buffer("GET /sensors/2/actual HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_ACTUAL);
    g_assert_cmpfloat_with_epsilon(received.get_actual,
                                   367.75, 0.1);
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
501");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_POST_MEASUREMENT);
  }
  {
    reset_buffer("GET /sensors/1/avg HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_AVG);
    g_assert_cmpfloat_with_epsilon(received.get_avg, 373.8,
                                   0.1);
  }
  {
    reset_buffer("GET /sensors/1/actual HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_ACTUAL);
    g_assert_cmpfloat_with_epsilon(received.get_actual, 501,
                                   0.1);
  }
}

void error_no_values() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_PUT_MODE_PASSIVE);
  }
  {
    reset_buffer("DELETE /sensors/1 HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_DELETE_MEASUREMENTS);
  }
  {
    reset_buffer("\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 1\r\n\
\r\n\
3");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==,
                    CREATED_201_PUT_CBUFFSIZE);
  }
  {
    reset_buffer("GET /sensors/1/avg HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_AVG);
    g_assert_cmpfloat_with_epsilon(received.get_avg, -1,
                                   0.1);
  }
  {
    reset_buffer("GET /sensors/1/stdev HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_STDEV);
    g_assert_cmpfloat_with_epsilon(received.get_stdev, -1,
                                   0.1);
  }
  {
    reset_buffer("GET /sensors/1/actual HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, OK_200_GET_ACTUAL);
    g_assert_cmpfloat_with_epsilon(received.get_actual, -1,
                                   0.1);
  }
}

void error_404_post() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("\
POST /sensors/3 HTTP/1.0\r\n\
Content-Length: 1\r\n\
\r\n\
0");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, NOT_FOUND_404);
  }
}

void error_404_get() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("GET /sensors/3/avg HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, NOT_FOUND_404);
    g_assert_cmpfloat_with_epsilon(received.get_avg, 0,
                                   0.1);
  }
}

void error_400_invalid_verb() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("IOT /sensors/1/actual HTTP/1.0\r\n\r\n");
    struct response received = handleRequest(stream);
    g_assert_cmpint(received.code, ==, BAD_REQUEST_400);
  }
}

int main(int argc, char** argv) {
  g_test_init(&argc, &argv, NULL);

  g_test_add_func("/single value 1", single_value_1);
  g_test_add_func("/single value 2", single_value_2);
  g_test_add_func("/multiple values", multiple_values);
  g_test_add_func("/cbuff overflow 1", cbuff_overflow_1);
  g_test_add_func("/cbuff overflow 2", cbuff_overflow_2);
  g_test_add_func("/complete", complete);
  g_test_add_func("/error no values", error_no_values);
  g_test_add_func("/error 404 post", error_404_post);
  g_test_add_func("/error 404 get", error_404_get);
  g_test_add_func("/error 400 invalid verb",
                  error_400_invalid_verb);

  return g_test_run();
}
