#ifndef token_h
#define token_h

#include "stream.h"
#include <stdbool.h>

#define TOKEN_LENGTH 20

enum tokentype {
  ERROR,       // no valid token, for instance, a sole \r
  UNAVAILABLE, // no more tokens available

  ALPHA, // %x41-5A / %x61-7A   A-Z / a-z
  CRLF,  // %x0D %x0A           \r\n
  DIGIT, // %x30-39             0-9
  HTAB,  // %x09                \t
  OCTET, // %x00-FF
  SP,    // %x20                space
  VCHAR // %x21-7E             visible (printing characters)
};

struct token {
  enum tokentype type;
  char value[TOKEN_LENGTH + 1];
};

// prepare tokenizer for next request
void initTokenizer();

// moet worden isTokenType, isTokenValue, isNotTokenType
// de unittests moeten worden aangevuld met de volledige set
// van HTTP constructies die uiteindelijk gebruikt worden.

// token look ahead
struct token peekToken(struct stream);
// remove token from stream
struct token readToken(struct stream);
// essentialle token look back (last read token)
struct token prevToken();

bool hasTokenType(struct token token, enum tokentype type);
bool hasTokenValue(struct token token, enum tokentype type,
                   const char* value);

#ifndef NDEBUG
void printToken(struct token);
#endif

#endif