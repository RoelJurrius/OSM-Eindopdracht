#include "buffermock.h"
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 200

struct {
  char text[MAX_LENGTH];
  int length;
  int current;
} buffer;

void reset_buffer(const char* text) {
  size_t inputLength;

  if (text == NULL) {
    buffer.text[0] = '\0';
    buffer.length = 0;
    buffer.current = 0;
    return;
  }

  inputLength = strlen(text);

  if (inputLength >= MAX_LENGTH) {
    printf("ERROR: input text too long\n");
    inputLength = MAX_LENGTH - 1;
  }

  strncpy(buffer.text, text, MAX_LENGTH - 1);
  buffer.text[MAX_LENGTH - 1] = '\0';
  buffer.length = (int)inputLength;
  buffer.current = 0;
}

int available_buffer() {
  return buffer.current < buffer.length;
}

char peek_buffer() {
  if (!available_buffer()) {
    return '\0';
  }

  return buffer.text[buffer.current];
}

char read_buffer() {
  char c = peek_buffer();

  if (available_buffer()) {
    buffer.current++;
  }

  return c;
}
