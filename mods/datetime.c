#include "../minibar.h"
#include <time.h>

int datetime(char *buf, size_t len, const char *fmt) {
  time_t t = time(NULL);
  return strftime(buf, len, fmt, localtime(&t)) ? 1 : 0;
}
