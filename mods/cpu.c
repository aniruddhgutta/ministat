#include "../ministat.h"
#include <stdlib.h>
#include <string.h>

int cpu(char *buf, size_t len, const char *arg) {
  double freq = 0.0;
  FILE *fp = fopen("/proc/cpuinfo", "r");
  if (!fp) {
    return 0;
  }

  while (!feof(fp)) {
    char label[64];
    double value;
    if (fscanf(fp, "%63s : %lf", label, &value) == 2) {
      if (strcmp(label, "cpu") == 0 || strcmp(label, "MHz") == 0) {
        freq = value;
        break;
      }
    }
  }
  fclose(fp);

  if (freq > 0.0) {
    if (freq >= 1000.0)
      snprintf(buf, len, "%.1fGHz", freq / 1000.0);
    else
      snprintf(buf, len, "%.0fMHz", freq);
    return 1;
  }

  return 0;
}
