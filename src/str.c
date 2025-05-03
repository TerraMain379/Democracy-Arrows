#include "./str.h"

size_t _strlen(char* str) {
  for (int i = 0;; i++) {
    if (str[i] == '\0') return i;
  }
}
struct Str Str_new(char* cstr) {
  return Str_new_byLen(cstr, _strlen(cstr));
}
struct Str Str_new_byLen(char* cstr, size_t len) {
  struct Str str;
  str.str = cstr;
  str.len = len;
  return str;
}
char Str_equals(struct Str str1, struct Str str2) {
  if (str1.len != str2.len) return 0;
  for (int i = 0; i < str1.len; i++) {
    if (str1.str[i] != str2.str[i]) return 0;
  }
  return 1;
}
