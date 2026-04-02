#include "response.h"

const char* statusLine(enum statuscode status) {
  switch (status) {
  case STATUS_200:
    return "HTTP/1.0 200 OK\r\n";
  case STATUS_201:
    return "HTTP/1.0 201 Created\r\n";
  case STATUS_400:
    return "HTTP/1.0 400 Bad Request\r\n";
  case STATUS_404:
    return "HTTP/1.0 404 Not Found\r\n";
  default:
    return "HTTP/1.0 400 Bad Request\r\n";
  }
}

const char* basicResponse(enum statuscode status) {
  switch (status) {
  case STATUS_200:
    return "HTTP/1.0 200 OK\r\n"
           "Connection: close\r\n"
           "\r\n";
  case STATUS_201:
    return "HTTP/1.0 201 Created\r\n"
           "Connection: close\r\n"
           "\r\n";
  case STATUS_400:
    return "HTTP/1.0 400 Bad Request\r\n"
           "Connection: close\r\n"
           "\r\n";
  case STATUS_404:
    return "HTTP/1.0 404 Not Found\r\n"
           "Connection: close\r\n"
           "\r\n";
  default:
    return "HTTP/1.0 400 Bad Request\r\n"
           "Connection: close\r\n"
           "\r\n";
  }
}