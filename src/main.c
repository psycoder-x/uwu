#include "tmtime.h"
#include "lib/str.h"
#include "stdio.h"
#include "stdlib.h"

typedef int(*MainFunc)(CharVV args);

typedef struct UtilHook {
  MainFunc func;
  CharV name;
} UtilHook;

int
help(CharVV args);

int
version(CharVV args);

const UtilHook HOOKS[] = {
  { .func = help, .name = CV_NTS("help") },
  { .func = version, .name = CV_NTS("version") },
  { .func = tmtime, .name = CV_NTS(TMTIME_CMD) }
};

int
main(int argc, char **argv) {
  CharV args_val[argc];
  CharVV args = cvv_mk(argc, args_val);
  for (size_t i = 0; i < args.size; i++) {
    args_val[i] = cv_nts(argv[i]);
  }
  /* help? */
  if (args.size < 2) {
    cv_writeln(CV("error: not enough arguments, try \"help\""), stderr);
    return 1;
  }
  /* find and call */
  for (size_t i = 0; i < sizeof(HOOKS)/sizeof(HOOKS[0]); i++) {
    if (cv_eq(HOOKS[i].name, args.at[1])) {
      return HOOKS[i].func(args);
    }
  }
  /* program not found */
  cv_writeln(CV("error: unknown program, try \"help\""), stderr);
  return 1;
}

int
help(CharVV args) {
  (void)args;
  cv_write(CV(
    "Usage: uwu <program> [options...]\n"
    "  help     Display this information\n"
    "  version  Display uwu version information\n"
    "  tmtime   Author\'s time to all medals\' time for TMNF track\n"
  ), stdout);
  return 0;
}

int
version(CharVV args) {
  (void)args;
  cv_write(CV(
    "UWU v0.1.0\n"
    "Copyright (C) 2023 psycoder-x\n"
    "License: MIT <https://spdx.org/licenses/MIT.html>\n"
  ), stdout);
  return 0;
}
