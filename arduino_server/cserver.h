#ifndef cserver_h
#define cserver_h

#include "stream.h"

#ifdef __cplusplus
extern "C" {
#endif

enum statuscode {
  BAD_REQUEST_400,
  NOT_FOUND_404,
  OK_200_GET_AVG,
  OK_200_GET_STDEV,
  OK_200_GET_ACTUAL,
  CREATED_201_PUT_MODE_ACTIVE,
  CREATED_201_PUT_MODE_PASSIVE,
  CREATED_201_PUT_CBUFFSIZE,
  CREATED_201_POST_MEASUREMENT,
  CREATED_201_DELETE_MEASUREMENTS
};

struct response {
  enum statuscode code;
  union {
    double get_avg;
    double get_stdev;
    double get_actual;
  };
};

struct response handleRequest(struct stream stream);
const char* handleResponse(struct stream stream);

#ifdef __cplusplus
}
#endif

#endif
