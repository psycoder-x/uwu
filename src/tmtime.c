#include "tmtime.h"
#include "stddef.h"
#include "stdbool.h"
#include "math.h"
#include "ctype.h"

static bool
get_time(CharV str_time, double *out_s);

static void
put_time(double time_s, FILE *stream);

static void
put_medal(CharV title, double time_s);

static bool
to_int(CharV str, unsigned long *out);

static bool
get_sec(CharV str_h_m_s, unsigned long *out_s);

static bool
get_min(CharV str_h_m, unsigned long *out_m);

int
tmtime(CharVV args) {
  /* secondary thing */
  if (args.size < 3) {
    cv_writeln(CV(
      "tmtime: error: not enough arguments, try \"help\""
    ), stderr);
    return 1;
  }
  if (cv_eq(CV("help"), args.at[2])) {
    cv_write(CV(
      "Usage: uwu "TMTIME_CMD" <time>|help|version\n"
      "  <time>   Author's time in format: [[h:]m:]s.ms\n"
      "  help     Display this information\n"
      "  version  Display "TMTIME_CMD" version\n"
    ), stdout);
    return 0;
  }
  if (cv_eq(CV("version"), args.at[2])) {
    cv_writeln(CV("UWU: "TMTIME_CMD" v1.0.0"), stdout);
    return 0;
  }
  /* main thing */
  double author_s = 0.0;
  if (!get_time(args.at[2], &author_s)) return 1;
  double gold_s = 1.04 * author_s;
  double silver_s = 1.1 * gold_s;
  double bronze_s = 1.1 * silver_s;
  put_medal(CV("Author: "), author_s);
  put_medal(CV("Gold:   "), gold_s);
  put_medal(CV("Silver: "), silver_s);
  put_medal(CV("Bronze: "), bronze_s);
  return 0;
}

void
put_medal(CharV title, double time_s) {
  cv_write(title, stdout);
  put_time(time_s, stdout);
  fputc('\n', stdout);
}

void
put_time(double time_s, FILE *stream) {
  unsigned long h = time_s / (60 * 60);
  time_s -= h * 60 * 60;
  unsigned long m = time_s / 60;
  time_s -= m * 60;
  unsigned long s = time_s;
  time_s -= s;
  unsigned long ms = time_s * 1000;
  if (h != 0) fprintf(stream, "%02i%c", h, ':'); 
  fprintf(stream, "%02i%c%02i%c%03i", m, ':', s, '.', ms);
}

bool
get_time(CharV str_time, double *out_s) {
  *out_s = 0.0;
  const Char *dot = cv_chr(str_time, '.');
  if (dot == NULL) {
    cv_writeln(CV(
      TMTIME_CMD": error: separator \'.\' not found"
    ), stderr);
    return false;
  }
  size_t doti = dot - str_time.at;
  CharV str_h_m_s = cv_get(str_time, doti);
  CharV str_ms = cv_cut(str_time, doti + 1);
  unsigned long time_ms = 0;
  unsigned long time_s = 0;
  if (!to_int(str_ms, &time_ms) || !get_sec(str_h_m_s, &time_s)) {
    return false;
  }
  *out_s = time_s + (double)time_ms / pow(10, str_ms.size);
  return true;
}

bool
to_int(CharV str, unsigned long *out) {
  *out = 0;
  for (size_t i = 0; i < str.size; i++) {
    if (!isdigit(str.at[i])) {
      cv_write(CV(TMTIME_CMD": error: "), stderr);
      cv_write(str, stderr);
      cv_writeln(CV(" is not decimal integer"), stderr);
      return false;
    }
    *out = *out * 10 + str.at[i] - '0';
  }
  return true;
}

bool
get_sec(CharV str_h_m_s, unsigned long *out_s) {
  const Char *semic = cv_rchr(str_h_m_s, ':');
  if (semic == NULL) return to_int(str_h_m_s, out_s);
  size_t semici = semic - str_h_m_s.at;
  CharV str_h_m = cv_get(str_h_m_s, semici);
  CharV str_s = cv_cut(str_h_m_s, semici + 1);
  unsigned long m = 0;
  if (!get_min(str_h_m, &m) || !to_int(str_s, out_s)) return false;
  *out_s += m * 60;
  return true;
}

bool
get_min(CharV str_h_m, unsigned long *out_m) {
  const Char *semic = cv_rchr(str_h_m, ':');
  if (semic == NULL) return to_int(str_h_m, out_m);
  size_t semici = semic - str_h_m.at;
  CharV str_h = cv_get(str_h_m, semici);
  CharV str_m = cv_cut(str_h_m, semici + 1);
  unsigned long h = 0;
  if (!to_int(str_h, &h) || !to_int(str_m, out_m)) return false;
  *out_m += h * 60;
  return true;
}
