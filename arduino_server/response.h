#ifndef response_h
#define response_h

enum statuscode {
  STATUS_200,
  STATUS_201,
  STATUS_400,
  STATUS_404
};

const char* statusLine(enum statuscode status);
const char* basicResponse(enum statuscode status);

#endif