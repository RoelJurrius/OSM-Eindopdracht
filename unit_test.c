#include "arduino_server/cserver.h"
#include "arduino_server/token.h"
#include "buffermock.h"
#include <glib.h>

void info_tokens() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};
  reset_buffer("\
GET /a HTTP/1.0\r\n\
\r\n\
");

  struct token next = readToken(stream);

  while (next.type != UNAVAILABLE) {
#ifndef NDEBUG
    printToken(next);
#else
    g_print(" %d", next.type);
#endif
    // https://docs.gtk.org/glib/func.printf.html
    g_print("\n");

    next = readToken(stream);
  }
}

void info_strncat() {
  char s1[10] = "hi ";
  char s2[100] = "there";

  strncat(s1, s2,
          10 - strlen(s1) - 1); // minus one for null char
  g_assert_cmpstr(s1, ==, "hi there");

  strncat(s1, "123", 10 - strlen(s1) - 1);
  g_assert_cmpstr(s1, ==, "hi there1");
}

// defined in abnf.c
void catValue(const char*, char[], size_t);

void info_catValue() {
  char txt[5] = "a";

  catValue("bc", txt, 5);
  g_assert_cmpstr(txt, ==, "abc");

  catValue("de", txt, 5);
  g_assert_cmpstr(txt, ==, "abcd");
}

void tokenizer_test_1() {

  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  const char* expectedValues[15] = {
      "a",    "b", " ", "C", "D", " ",  "1", "2",
      "\r\n", "/", ".", ":", " ", "\b", "\r"};
  const enum tokentype expectedTypes[15] = {
      ALPHA, ALPHA, SP,    ALPHA, ALPHA,
      SP,    DIGIT, DIGIT, CRLF,  VCHAR,
      VCHAR, VCHAR, SP,    OCTET, ERROR};

  reset_buffer("\
ab CD 12\r\n\
/.: \b\r\
");

  for (int i = 0; i < 15; i++) {
    struct token got = readToken(stream);
    g_assert_cmpstr(got.value, ==, expectedValues[i]);
    g_assert_cmpint(got.type, ==, expectedTypes[i]);
  }
}

void tokenizer_test_2() {

  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  reset_buffer("E");

  struct token got = readToken(stream);

  g_assert_true(hasTokenType(got, ALPHA));
  g_assert_true(hasTokenType(got, VCHAR));
  g_assert_true(hasTokenType(got, OCTET));
}

void simple_requesttarget() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  reset_buffer("\
GET / HTTP/1.0\r\n\
\r\n\
");

  g_assert_true(handleRequest(stream));
}

void single_value_1() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("DELETE /sensors/1 HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
10");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
228");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("GET /sensors/1/avg HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("GET /sensors/1/stdev HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("GET /sensors/1/actual HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
}

void single_value_2() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("DELETE /sensors/2 HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
10");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
51");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("GET /sensors/2/avg HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("GET /sensors/2/stdev HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("GET /sensors/2/actual HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
}

void multiple_values() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("DELETE /sensors/1 HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("DELETE /sensors/2 HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
14");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
501");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
457");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
285");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
209");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
178");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
864");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
65");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
61");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
191");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
447");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
476");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
54");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
407");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
859");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("GET /sensors/1/avg HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("GET /sensors/1/stdev HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("GET /sensors/1/actual HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
451");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
919");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
569");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 2\r\n\
\r\n\
13");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
326");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
865");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/2 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
696");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("GET /sensors/2/avg HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("GET /sensors/2/stdev HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("GET /sensors/2/actual HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
}

void cbuff_overflow_1() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("\
PUT /config/mode HTTP/1.0\r\n\
Content-Length: 7\r\n\
\r\n\
passive");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
PUT /config/cbuffsize HTTP/1.0\r\n\
Content-Length: 1\r\n\
\r\n\
5");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
318");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
440");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
689");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
209");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
189");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
778");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("\
POST /sensors/1 HTTP/1.0\r\n\
Content-Length: 3\r\n\
\r\n\
198");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("GET /sensors/1/avg HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("GET /sensors/1/stdev HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
  {
    reset_buffer("GET /sensors/1/actual HTTP/1.0\r\n\r\n");
    g_assert_true(handleRequest(stream));
  }
}

void error_empty() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("");
    g_assert_false(handleRequest(stream));
  }
}

void error_start_line_1() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("GET  /sensors HTTP/1.0\r\n\r\n");
    g_assert_false(handleRequest(stream));
  }
}

void error_start_line_2() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("GET /sensors HTTP/1.0");
    g_assert_false(handleRequest(stream));
  }
}

void error_start_line_3() {
  struct stream stream = {.available = available_buffer,
                          .peek = peek_buffer,
                          .read = read_buffer};

  {
    reset_buffer("GET /sensors /data HTTP/1.0\r\n\r\n");
    g_assert_false(handleRequest(stream));
  }
}

int main(int argc, char** argv) {
  g_test_init(&argc, &argv, NULL);

  g_test_add_func("/info 1", info_tokens);
  g_test_add_func("/info 2", info_strncat);
  g_test_add_func("/info 3", info_catValue);

  // initially, tests fail and cppcheck complains

  g_test_add_func("/token test 1", tokenizer_test_1);
  g_test_add_func("/token test 2", tokenizer_test_2);

  g_test_add_func("/simple 1", simple_requesttarget);

  g_test_add_func("/single value 1", single_value_1);
  g_test_add_func("/single value 2", single_value_2);
  g_test_add_func("/multiple values", multiple_values);
  g_test_add_func("/cbuff overflow 1", cbuff_overflow_1);

  g_test_add_func("/error empty 1", error_empty);
  g_test_add_func("/error startline 1", error_start_line_1);
  g_test_add_func("/error startline 2", error_start_line_2);
  g_test_add_func("/error startline 3", error_start_line_3);

  return g_test_run();
}
