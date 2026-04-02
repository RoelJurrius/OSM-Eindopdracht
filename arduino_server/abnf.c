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
static bool get_method(struct stream stream);
static bool post_method(struct stream stream);
static bool put_method(struct stream stream);
static bool delete_method(struct stream stream); 

static bool readTokenType(struct stream, enum tokentype);
static bool readTokenValue(struct stream, enum tokentype,
                           const char*);
// catValue is not static to allow for an informative test
void catValue(const char*, char[], size_t);

static bool path_char(struct stream stream) ;
static bool path_segment(struct stream stream) ;
static bool ows(struct stream stream) ;


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

  while (field_line(stream)) {
    if (!readTokenType(stream, CRLF)) {
      return false;
    }
  }

  if (!readTokenType(stream, CRLF)) {
    return false;
  }

  message_body(stream);
  return true;
}

// remaining ABFN functions are stubs

static bool field_line(struct stream stream) {
  if (!field_name(stream)) {
    return false;
  }

  if (!readTokenValue(stream, VCHAR, ":")) {
    return false;
  }

  ows(stream);
  field_value(stream);
  return true;
}

static bool field_name(struct stream stream) {
  if (!tchar(stream, NULL, 0)) {
    return false;
  }

  while (tchar(stream, NULL, 0)) {
    ;
  }

  return true;
}

static bool field_value(struct stream stream) {
  while (readTokenType(stream, VCHAR) || readTokenType(stream, SP)) {
    ;
  }
  return true;
}

static bool http_token(struct stream stream) {
  return false;
}

static bool http_version(struct stream stream) {
  return readTokenValue(stream, ALPHA, "H") &&
         readTokenValue(stream, ALPHA, "T") &&
         readTokenValue(stream, ALPHA, "T") &&
         readTokenValue(stream, ALPHA, "P") &&
         readTokenValue(stream, VCHAR, "/") &&
         readTokenValue(stream, DIGIT, "1") &&
         readTokenValue(stream, VCHAR, ".") &&
         readTokenValue(stream, DIGIT, "0");
}

static bool message_body(struct stream stream) {
  while (readTokenType(stream, VCHAR) ||
         readTokenType(stream, SP) ||
         readTokenType(stream, CRLF)) {
    ;
  }
  return true;
}

static bool method(struct stream stream) {
  return get_method(stream) ||
         post_method(stream) ||
         put_method(stream) ||
         delete_method(stream);
}

static bool request_line(struct stream stream) {
  if (!method(stream)) {
    return false;
  }

  if (!readTokenType(stream, SP)) {
    return false;
  }

  if (!request_target(stream)) {
    return false;
  }

  if (!readTokenType(stream, SP)) {
    return false;
  }

  if (!http_version(stream)) {
    return false;
  }

  return true;
}

static bool request_target(struct stream stream) {
  if (!readTokenValue(stream, VCHAR, "/")) {
    return false;
  }

  if (!path_segment(stream)) {
    return false;
  }

  while (readTokenValue(stream, VCHAR, "/")) {
    if (!path_segment(stream)) {
      return false;
    }
  }

  return true;
}

static bool origin_form(struct stream stream) {
  return false;
}

static bool start_line(struct stream stream) {
  return request_line(stream);
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

static bool get_method(struct stream stream) {
  return readTokenValue(stream, ALPHA, "G") &&
         readTokenValue(stream, ALPHA, "E") &&
         readTokenValue(stream, ALPHA, "T");
}

static bool post_method(struct stream stream) {
  return readTokenValue(stream, ALPHA, "P") &&
         readTokenValue(stream, ALPHA, "O") &&
         readTokenValue(stream, ALPHA, "S") &&
         readTokenValue(stream, ALPHA, "T");
}

static bool put_method(struct stream stream) {
  return readTokenValue(stream, ALPHA, "P") &&
         readTokenValue(stream, ALPHA, "U") &&
         readTokenValue(stream, ALPHA, "T");
}

static bool delete_method(struct stream stream) {
  return readTokenValue(stream, ALPHA, "D") &&
         readTokenValue(stream, ALPHA, "E") &&
         readTokenValue(stream, ALPHA, "L") &&
         readTokenValue(stream, ALPHA, "E") &&
         readTokenValue(stream, ALPHA, "T") &&
         readTokenValue(stream, ALPHA, "E");
}

static bool path_char(struct stream stream) {
  return readTokenType(stream, ALPHA) ||
         readTokenType(stream, DIGIT) ||
         readTokenValue(stream, VCHAR, "_");
}

static bool path_segment(struct stream stream) {
  if (!tchar(stream, NULL, 0)) {
    return false;
  }

  while (tchar(stream, NULL, 0)) {
    ;
  }

  return true;
}

static bool ows(struct stream stream) {
  while (readTokenType(stream, SP)) {
    ;
  }
  return true;
}