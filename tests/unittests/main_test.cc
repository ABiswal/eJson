#include <gtest/gtest.h>
#include "jsont.hh"
#include "eJson.hh"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define JSONT_ASSERT_FIELD_NAME(fieldName) do { \
  assert(jsont_current(S) == JSONT_FIELD_NAME); \
  assert(jsont_data_equals(S, (const uint8_t*)fieldName, \
    strlen(fieldName)) == true); \
} while(0)

TEST(eJsonTest, BasicAssertions){

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
  EXPECT_EQ(tok,jsont::Token::ObjectStart);
  EXPECT_EQ(S.current(),jsont::Token::ObjectStart);
  
  tok = S.next();
  EXPECT_EQ(tok,jsont::Token::FieldName);

  
  // Expect current data to be the bytes '"fo"o'
  const char* expectedData = "\"fo\"o";
  const char * bytes;
  size_t size = S.dataValue(&bytes);
  size_t expectedSize = strlen(expectedData);
  // printf("expectedData: '%s'\n", expectedData);
  // printf("currentData:  '%.*s'\n", (int)size, (const char*)bytes);
  assert(size == expectedSize);
  int d = memcmp((const void*)expectedData, bytes, size);
  assert(d == 0);

  // Expect a string value "Foo"
  tok = S.next();
  EXPECT_EQ(tok,jsont::Token::String);
  std::string str = S.stringValue();
  assert(str != 0);
  assert(strcmp(str, "Foo") == 0);
  //free(str); str = 0;

  // Expect field name "1". Also tests the integrity of jsont_data_equals
  tok = S.next();
  //assert(jsont_data_equals(S, (const uint8_t*)"1", 1) == true);
  //assert(jsont_str_equals(S, "1") == true);
  size = S.dataValue(&bytes);
  assert(size == 1);
  assert(memcmp((const void*)"1", (const void*)bytes, 1) == 0);

  

  // Expect the string '\u2192' (RIGHTWARDS ARROW, UTF8: E2,86,92)
  //assert(jsont_next(S) == JSONT_STRING);
  //assert(jsont_str_equals(S, "\xe2\x86\x92") == true);
  
  tok = S.next();
  EXPECT_EQ(tok,jsont::Token::String);
  str = S.stringValue();
  assert(str != 0);
  EXPECT_EQ(str, "\xe2\x86\x92");
  #if 0
  // Expect a field name 'n'
  jsont_next(S);
  JSONT_ASSERT_FIELD_NAME("n");

  // Expect a number value '1234'
  assert(jsont_next(S) == JSONT_NUMBER_INT);
  //printf("int: %lld (str: '%s')\n", jsont_int_value(S), jsont_strcpy_value(S));
  assert(jsont_int_value(S) == 1234LL);
  assert(jsont_float_value(S) == 1234.0);

  // Expect a field name 'x'
  jsont_next(S);
  JSONT_ASSERT_FIELD_NAME("x");

  // Expect a number value '12.34'
  assert(jsont_next(S) == JSONT_NUMBER_FLOAT);
  assert(jsont_float_value(S) == 12.34);
  assert(jsont_int_value(S) == 12LL); // partial expected

  jsont_next(S);
  JSONT_ASSERT_FIELD_NAME("overflow");

  // Expect a cut-off integer value of INT64_MAX
  assert(jsont_next(S) == JSONT_NUMBER_INT);
  assert(jsont_int_value(S) == INT64_MAX);

  // Expect a valid floating point value (although it will have less-than
  // perfect precision)
  assert(!isnan(jsont_float_value(S)));

  // Expect a field name 'bar'
  jsont_next(S);
  JSONT_ASSERT_FIELD_NAME("b/a/r");

  // Expect start of array
  assert(jsont_next(S) == JSONT_ARRAY_START);

  // Expect null, true and false
  assert(jsont_next(S) == JSONT_NULL);
  assert(jsont_next(S) == JSONT_TRUE);
  assert(jsont_next(S) == JSONT_FALSE);

  // { "x": 12.3 }
  assert(jsont_next(S) == JSONT_OBJECT_START);
  jsont_next(S);
  JSONT_ASSERT_FIELD_NAME("x");
  assert(jsont_next(S) == JSONT_NUMBER_FLOAT);
  assert(jsont_float_value(S) == 12.3);
  assert(jsont_next(S) == JSONT_OBJECT_END);

  // 123, "456", "a\"b\""
  assert(jsont_next(S) == JSONT_NUMBER_INT);
  assert(jsont_int_value(S) == 123);

  assert(jsont_next(S) == JSONT_STRING);
  assert(jsont_str_equals(S, "456") == true);

  assert(jsont_next(S) == JSONT_STRING);
  assert(jsont_str_equals(S, "a\"b\"") == true);

  // "a\u0000b"
  assert(jsont_next(S) == JSONT_STRING);
  const uint8_t b3[] = {'a',0,'b'};
  assert(jsont_data_equals(S, b3, sizeof(b3)) == true);

  // "a\{b,f,n,r,t}b"
  assert(jsont_next(S) == JSONT_STRING);
  assert(jsont_str_equals(S, "a\bb") == true);
  assert(jsont_next(S) == JSONT_STRING);
  assert(jsont_str_equals(S, "a\fb") == true);
  assert(jsont_next(S) == JSONT_STRING);
  assert(jsont_str_equals(S, "a\nb") == true);
  assert(jsont_next(S) == JSONT_STRING);
  assert(jsont_str_equals(S, "a\rb") == true);
  assert(jsont_next(S) == JSONT_STRING);
  assert(jsont_str_equals(S, "a\tb") == true);

  // ""
  assert(jsont_next(S) == JSONT_STRING);
  assert(jsont_str_equals(S, "") == true);
  assert(jsont_str_equals(S, "   ") == false);

  // "   "
  assert(jsont_next(S) == JSONT_STRING);
  assert(jsont_str_equals(S, "   ") == true);
  assert(jsont_str_equals(S, "") == false);

  // ] }
  assert(jsont_next(S) == JSONT_ARRAY_END);
  assert(jsont_next(S) == JSONT_OBJECT_END);
  #endif

  //jsont_destroy(S);
  //printf("PASS\n");

  
}

/* Uncomment the below test case if required
*  the eJson files must be present in work/unittests folder
*/
#if 0
TEST(eJson, FileImport){
  eJson::eJsonTokenizer E("test.eJson");
  jsont::Token tok;
  tok=E.tockenizer.next();
  
  EXPECT_EQ(tok,jsont::Token::ObjectStart);
  EXPECT_EQ(E.tockenizer.current(),jsont::Token::ObjectStart);
}
#endif
