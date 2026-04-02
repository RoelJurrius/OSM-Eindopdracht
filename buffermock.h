#ifndef buffermock_h
#define buffermock_h

#include "arduino_server/stream.h"

void reset_buffer(const char*);
int available_buffer();
char read_buffer();
char peek_buffer();


#endif
