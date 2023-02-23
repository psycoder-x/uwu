#include "str.h"
#include "string.h"

CharV
cv_mk(size_t size, const Char *data) {
  return (CharV) {
    .size = (data == NULL) ? 0 : size,
    .at = data
  };
}

CharV
cv_nts(const char *nts) {
  return cv_mk(strlen(nts), (const Char *)nts);
}

bool
cv_eq(CharV str1, CharV str2) {
  if (str1.size != str2.size) return false;
  return memcmp(str1.at, str2.at, str1.size) == 0;
}

CharV
cv_get(CharV string, size_t count) {
  if (string.size <= count) return string;
  return cv_mk(count, string.at);
}

CharV
cv_cut(CharV string, size_t count) {
  if (string.size <= count) return cv_mk(0, string.at + string.size);
  return cv_mk(string.size - count, string.at + count);
}

const Char *
cv_chr(CharV string, Char character) {
  for (size_t i = 0; i < string.size; i++) {
    if (string.at[i] == character) {
      return &string.at[i];
    }
  }
  return NULL;
}

const Char *
cv_rchr(CharV string, Char character) {
  for (size_t k = 0, i = string.size - 1; k < string.size; k++, i--) {
    if (string.at[i] == character) {
      return &string.at[i];
    }
  }
  return NULL;
}

size_t
cv_write(CharV string, FILE *stream) {
  return fwrite(string.at, sizeof(Char), string.size, stream);
}

size_t
cv_writeln(CharV string, FILE *stream) {
  size_t n = cv_write(string, stream);
  fputc('\n', stream);
  return n;
}

CharVV
cvv_mk(size_t size, const CharV *data) {
  return (CharVV) {
    .size = (data == NULL) ? 0 : size,
    .at = data
  };
}
