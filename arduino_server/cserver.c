#include "cserver.h"
#include "abnf.h"

// cppcheck-suppress unusedFunction
bool handleRequest(struct stream stream) {
  return http_message(stream);
}
