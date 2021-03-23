#include <stdarg.h>
#include "utils.h"
#include "errors.h"
#include "ename.h"

int main(void) {
  printf("Hello world");

  return 0;
}

#ifdef __GNUC__
__attribute__ ((__noreturn__))
#endif
static void terminate(bool use_std_exit) {
  char *s;
  /**
   * Dump core if EF_DUMPCORE environment is defined around
   * is a nonempty string; otherwise call exit(), or _exit()
   */

  s = getenv("EF_DUMPCORE");

  if (!str_is_empty(s)) {
    abort();
  } else if (use_std_exit) {
    exit(EXIT_FAILURE);
  } else {
    _exit(EXIT_FAILURE);
  }
}

static void output_error(bool use_err, int err, 
    bool flush_stdout, const char* format, va_list ap) {

  #define BUF_SIZE 500
  char buf[BUF_SIZE], user_msg[BUF_SIZE], err_text[BUF_SIZE];

  vsnprintf(user_msg, BUF_SIZE, format, ap);

  if (use_err) {
    snprintf(err_text, BUF_SIZE, " [%s %s]", 
        (err > 0 && err <= MAX_ENAME) ? ename[err] : "?UNKNOWN?", strerror(err));
  } else {
    snprintf(err_text, BUF_SIZE, ":");
  }

  snprintf(buf, BUF_SIZE, "ERROR%s %s\n", err_text, user_msg);

  if (flush_stdout) {
    fflush(stdout);
  }
  fputs(buf, stderr);
  fflush(stderr);
}

void err_msg(const char* format, ...) {
  va_list arg_list;
  const int saved_errno = errno;

  va_start(arg_list, format);
  output_error(true, errno, true, format, arg_list);
  va_end(arg_list);

  errno = saved_errno;
}

void err_msg_exit(const char* format, ...) {
  va_list arg_list;

  va_start(arg_list, format);
  output_error(true, errno, true, format, arg_list);
  va_end(arg_list);

  terminate(true);
}

void err_msg_num_exit(int errnum, const char* format, ...) {
  va_list arg_list;

  va_start(arg_list, format);
  output_error(true, errnum, true, format, arg_list);
  va_end(arg_list);

  terminate(true);
}

void err_exit(const char* format, ...) {
  va_list arg_list;

  va_start(arg_list, format);
  output_error(true, errno, false, format, arg_list);
  va_end(arg_list);

  terminate(false);
}

void fatal(const char* format, ...) {
  va_list arg_list;

  va_start(arg_list, format);
  output_error(false, 0, true, format, arg_list);
  va_end(arg_list);

  terminate(true);
}

void usage_err(const char* format, ...) {
  va_list arg_list;

  fflush(stdout);
  fprintf(stderr, "Usage: ");
  va_start(arg_list, format);
  vfprintf(stderr, format, arg_list);
  va_end(arg_list);

  fflush(stderr);
  exit(EXIT_FAILURE);
}

void cmd_line_err(const char* format, ...) {
  va_list arg_list;

  fflush(stdout);

  fprintf(stderr, "Command-line usage error: ");
  va_start(arg_list, format);
  vfprintf(stderr, format, arg_list);
  va_end(arg_list);

  fflush(stderr);
  exit(EXIT_FAILURE);
}

