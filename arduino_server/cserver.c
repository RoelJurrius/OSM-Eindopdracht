#include "abnf.h"
#include "cserver.h"
#include "response.h"

bool handleRequest(struct stream stream) {
  return http_message(stream);
}

const char* handleResponse(struct stream stream) {
  if (handleRequest(stream)) {
    return basicResponse(STATUS_200);
  }

  return basicResponse(STATUS_400);
}