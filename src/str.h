#pragma once
#include <stdint.h>

struct Str {
  size_t len;
  char* str;
};
struct Str Str_new(char* str);
struct Str Str_new_byLen(char* cstr, size_t len);
char Str_equals(struct Str str1, struct Str str2);
