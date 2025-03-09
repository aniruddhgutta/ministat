#include "../minibar.h"
#include <stdio.h>
#include <string.h>

int ram(char *buf, size_t len, const char *arg) {
  FILE *fp = fopen("/proc/meminfo", "r");
  if (!fp) return 0;

  unsigned long total = 0, free = 0, cached = 0, buffers = 0, sreclaim = 0, shmem = 0;
  char key[32];
  unsigned long value;

  while (fscanf(fp, "%31s %lu kB\n", key, &value) != EOF) {
    if (!strcmp(key, "MemTotal:")) total = value;
    else if (!strcmp(key, "MemFree:")) free = value;
    else if (!strcmp(key, "Buffers:")) buffers = value;
    else if (!strcmp(key, "Cached:")) cached = value;
    else if (!strcmp(key, "SReclaimable:")) sreclaim = value;
    else if (!strcmp(key, "Shmem:")) shmem = value;
  }
  fclose(fp);

  unsigned long used = total - free - cached - buffers - sreclaim + shmem;
  return snprintf(buf, len, "%lu", used / 1024) >= 0;
}
