
#include "jsont.hh"

int main() {
  
  const char* inbuf = "{ "
    "\"\\\"fo\\\"o\": \"Foo\","  // "\"fo\"o": "Foo"
    "\"1\" :  \"\\u2192\","
    "\"n\":1234,"
    "\"x\"  :  \t 12.34,"
    "\"overflow\"  :  \t 9999999999999999999999999999999999,"
    "\"b\\/a\\/r\":["
      "null,"
      "true,"
      "false,"
      "{"
        "\"x\":12.3"
      "},"
      "\n123,"
      "\"456\","
      "\"a\\\"b\\\"\","
      "\"a\\u0000b\","
      "\"a\\bb\","
      "\"a\\fb\","
      "\"a\\nb\","
      "\"a\\rb\","
      "\"a\\tb\","
      "\"\","
      "\"   \""
    "]"
  "}";

  jsont::Tokenizer S((const char *)inbuf, strlen(inbuf),jsont::TextEncoding::UTF8TextEncoding);

  S.reset((const char *)inbuf, strlen(inbuf),jsont::TextEncoding::UTF8TextEncoding);
  jsont::Token tok;

  tok = S.next();
  printf("tocken %d",tok);
}
