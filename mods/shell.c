#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <string.h>

int shell(char *out, size_t n, const char *cmd)
{
  FILE *fp;
  if (!(fp = popen(cmd, "r"))) {
    *out = '\0';
    return 0;
  }
  if (!fgets(out, n, fp)) {
    pclose(fp);
    *out = '\0';
    return 0;
  }
  pclose(fp);
  out[strcspn(out, "\n")] = '\0';
  return strlen(out);
}
