#ifndef cserver_h
#define cserver_h

#include "stream.h"
#include <stdbool.h> // ik denk dat deze hier overbodig is


bool handleRequest(struct stream);

/*

// Op moment dat je overgaat van unittests naar integratietests
// krijgt `handleRequest` een nieuw return-type.
// Zonder het nu te controleren, verwacht ik dat de onderstaande
// definitie werkt.

enum statuscode {
  INTERNAL_SERVER_ERROR_500, // failed to malloc cbuffers
  BAD_REQUEST_400,           // bad request
  NOT_FOUND_404,             // request target not found
  OK_200_GET_AVG,            // get mean
  OK_200_GET_STDEV,          // get standard deviation
  OK_200_GET_ACTUAL,         // empty cbuffer, get its mean
  CREATED_201_PUT_MODE_ACTIVE,    // start reading sensors
  CREATED_201_PUT_MODE_PASSIVE,   // stop reading sensors
  CREATED_201_PUT_CBUFFSIZE,      // send new cbuffer size
  CREATED_201_POST_MEASUREMENT,   // send a measurement
  CREATED_201_DELETE_MEASUREMENTS // clear collected data
};

struct response {
  enum statuscode code;
  union {
    double get_avg;
    double get_stdev;
    double get_actual;
  };
};

struct response handleRequest(struct stream);
*/

#endif
