#include "../minibar.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

int
temp(char *buf, size_t len, const char *hwmon)
{
  char path[PATH_MAX];
  FILE *fp;
  int temp;

  if (!hwmon || !*hwmon)
    return snprintf(buf, len, "?");

  snprintf(path, sizeof(path), "/sys/class/hwmon/%s/temp1_input", hwmon);

  fp = fopen(path, "r");
  if (!fp)
    return snprintf(buf, len, "?");

  if (fscanf(fp, "%d", &temp) != 1) {
    fclose(fp);
    return snprintf(buf, len, "?");
  }

  fclose(fp);
  return snprintf(buf, len, "%d", temp / 1000);
}
