#ifndef LIB_STR_H
#define LIB_STR_H

#include "stddef.h"
#include "stdbool.h"
#include "stdio.h"

typedef unsigned char Char;

typedef struct CharV {
  size_t size;
  const Char *at;
} CharV;

typedef struct CharVV {
  size_t size;
  const CharV *at;
} CharVV;

#define CV_NTS(NTS) \
  { .size = sizeof(NTS) - 1, .at = (const Char *)NTS }

#define CV(NTS) \
  (CharV) { .size = sizeof(NTS) - 1, .at = (const Char *)NTS }

CharV
cv_mk(size_t size, const Char *data);

CharV
cv_nts(const char *nts);

bool
cv_eq(CharV str1, CharV str2);

CharV
cv_get(CharV string, size_t count);

CharV
cv_cut(CharV string, size_t count);

const Char *
cv_chr(CharV string, Char character);

const Char *
cv_rchr(CharV string, Char character);

size_t
cv_write(CharV string, FILE *stream);

size_t
cv_writeln(CharV string, FILE *stream);

CharVV
cvv_mk(size_t size, const CharV *data);

#endif /* LIB_STR_H */
