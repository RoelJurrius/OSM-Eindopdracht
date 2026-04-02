#include "abnf.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool field_line(struct stream);
static bool field_name(struct stream);
static bool field_value(struct stream);
static bool http_token(struct stream);
static bool http_version(struct stream);
static bool message_body(struct stream);
static bool method(struct stream);
static bool origin_form(struct stream);
static bool request_line(struct stream);
static bool request_target(struct stream);
static bool start_line(struct stream);
static bool tchar(struct stream, char[], size_t);

static bool readTokenType(struct stream, enum tokentype);
static bool readTokenValue(struct stream, enum tokentype,
                           const char*);
// catValue is not static to allow for an informative test
void catValue(const char*, char[], size_t);

bool http_message(struct stream stream) {
  initTokenizer();

  // ABNF for http_message is an AND construction, so early
  // exit on error

  if (!start_line(stream)) {
    return false;
  }

  if (!readTokenType(stream, CRLF)) {
    return false;
  }

  while (field_line(stream) &&
         readTokenType(stream, CRLF)) {
    ;
  }

  if (!readTokenType(stream, CRLF)) {
    return false;
  }

  if (message_body(stream)) {
    ;
  }

  return true;
}

// remaining ABFN functions are stubs

static bool field_line(struct stream stream) {
  return false;
}

static bool field_name(struct stream stream) {
  return false;
}

static bool field_value(struct stream stream) {
  return false;
}

static bool http_token(struct stream stream) {
  return false;
}

static bool http_version(struct stream stream) {
  return false;
}

static bool message_body(struct stream stream) {
  return false;
}

static bool method(struct stream stream) { return false; }

static bool request_line(struct stream stream) {
  return false;
}

static bool request_target(struct stream stream) {
  return false;
}

static bool origin_form(struct stream stream) {
  return false;
}

static bool start_line(struct stream stream) {
  return false;
}

static bool tchar(struct stream stream, char result[],
                  size_t len) {
  struct token next = peekToken(stream);

  if (next.type == DIGIT) {
    next = readToken(stream);
    catValue(next.value, result, len);
    return true;
  }

  if (next.type == ALPHA) {
    next = readToken(stream);
    catValue(next.value, result, len);
    return true;
  }

  if (next.type == VCHAR) {
    switch (next.value[0]) {
    case '!': // falls through on purpose
    case '#':
    case '$':
    case '%':
    case '&':
    case '\'':
    case '*':
    case '+':
    case '-':
    case '.':
    case '^':
    case '`':
    case '|':
    case '~':
      next = readToken(stream);
      catValue(next.value, result, len);
      return true;
    }
  }

  return false;
}

static bool readTokenType(struct stream stream,
                          enum tokentype type) {
  struct token next = peekToken(stream);

  if (!hasTokenType(next, type)) {
    return false;
  }

  readToken(stream);
  return true;
}

static bool readTokenValue(struct stream stream,
                           enum tokentype type,
                           const char* value) {
  struct token next = peekToken(stream);

  if (!hasTokenValue(next, type, value)) {
    return false;
  }

  readToken(stream);
  return true;
}

void catValue(const char* value, char result[],
              size_t len) {
  if (len == 0) {
    return;
  }
  strncat(result, value, len - strlen(result) - 1);
}