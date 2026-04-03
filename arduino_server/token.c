#include "token.h"
#include <stdio.h>
#include <string.h>

static struct token getNextToken(struct stream);
static struct token getCrlfToken(struct stream,
                                 struct token tok);

static bool isVchar(char c);
static bool isDigit(char c);
static bool isAlpha(char c);

static bool _buffersToken = false;
static struct token _currentToken, _previousToken;

void initTokenizer() { _buffersToken = false; }

struct token readToken(struct stream stream) {
  _previousToken = _currentToken;

  if (!_buffersToken) {
    _currentToken = getNextToken(stream);
  }

  _buffersToken = false;
  return _currentToken;
}

struct token peekToken(struct stream stream) {
  if (!_buffersToken) {
    _currentToken = readToken(stream);
    _buffersToken = true;
  }

  return _currentToken;
}

struct token prevToken() { return _previousToken; }

bool hasTokenType(struct token token, enum tokentype type) {
  if (token.type == type) {
    return true;
  }

  // some token types overlap
  if ((token.type == ALPHA || token.type == DIGIT) &&
      type == VCHAR) {
    return true;
  }

  if ((token.type == ALPHA || token.type == DIGIT ||
       token.type == VCHAR) &&
      type == OCTET) {
    return true;
  }

  return false;
}

bool hasTokenValue(struct token token, enum tokentype type,
                   const char* value) {
  if (!hasTokenType(token, type)) {
    return false;
  }

  if (strlen(value) > TOKEN_LENGTH) {
    return false;
  }

  return strncmp(token.value, value, TOKEN_LENGTH) == 0;
}

static struct token getNextToken(struct stream stream) {
  struct token tok = {.type = ERROR};
  memset(tok.value, '\0', TOKEN_LENGTH + 1);

  if (!stream.available()) {
    tok.type = UNAVAILABLE;
    return tok;
  }

  char peek = stream.peek();

  switch (peek) {
  case ' ':
    tok.value[0] = stream.read();
    tok.type = SP;
    return tok;
  case '\t':
    tok.value[0] = stream.read();
    tok.type = HTAB;
    return tok;
  case '\r':
    return getCrlfToken(stream, tok);
  }

  if (isAlpha(peek)) {
    tok.value[0] = stream.read();
    tok.type = ALPHA;
    return tok;
  }

  if (isDigit(peek)) {
    tok.value[0] = stream.read();
    tok.type = DIGIT;
    return tok;
  }

  if (isVchar(peek)) {
    tok.value[0] = stream.read();
    tok.type = VCHAR;
    return tok;
  }

  tok.value[0] = stream.read();
  tok.type = OCTET;
  return tok;
}

static struct token getCrlfToken(struct stream stream,
                                 struct token tok) {
  tok.value[0] = stream.read();

  if (stream.peek() != '\n') {
    tok.type = ERROR;
    return tok;
  }

  tok.value[1] = stream.read();
  tok.type = CRLF;

  return tok;
}

static bool isDigit(char c) { return c >= '0' && c <= '9'; }

// https://en.cppreference.com/w/c/string/byte - isalpha
static bool isAlpha(char c) {
  if (c >= 'a' && c <= 'z') {
    return true;
  }
  if (c >= 'A' && c <= 'Z') {
    return true;
  }
  return false;
}

static bool isVchar(char c) {
  return c >= 0x21 && c <= 0x7E;
}

#ifndef NDEBUG
// cppcheck-suppress unusedFunction
void printToken(struct token tok) {
  switch (tok.type) {
  case ERROR:
    printf("ERROR");
    break;
  case UNAVAILABLE:
    printf("UNAVAILABLE");
    break;
  case ALPHA:
    printf("ALPHA");
    break;
  case CRLF:
    printf("CRLF");
    break;
  case DIGIT:
    printf("DIGIT");
    break;
  case HTAB:
    printf("HTAB");
    break;
  case OCTET:
    printf("OCTET");
    break;
  case SP:
    printf("SP");
    break;
  case VCHAR:
    printf("VCHAR");
    break;
  }

  if (hasTokenType(tok, VCHAR)) {
    printf(": \"%s\"", tok.value);
  } else {
    printf(" (hex):");
    // https://stackoverflow.com/a/12725151
    const char* s = tok.value;
    while (*s) {
      printf(" %02x", (unsigned int)*s++);
    }
  }
}
#endif