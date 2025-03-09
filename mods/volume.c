#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *icons[] = {
  "󰝟", /* Muted */
  "󰕿", /* 0 */
  "󰖀", /* 1–50 */
  "󰕾"  /* 51+ */
};

int
volume(char *buf, size_t len, const char *fmt)
{
  FILE *fp;
  char line[128] = {0};
  int vol = -1;
  int muted = 0;

  fp = popen("wpctl get-volume @DEFAULT_AUDIO_SINK@", "r");
  if (fp && fgets(line, sizeof(line), fp)) {
    double fvol = 0.0;
    if (sscanf(line, "Volume: %lf", &fvol) == 1) {
      vol = (int)(fvol * 100);
    }
    muted = strstr(line, "[MUTED]") != NULL;
  }
  if (fp) pclose(fp);

  if (muted || vol == -1)
    return snprintf(buf, len, fmt ? fmt : "%s", icons[0]);

  const char *icon = vol == 0 ? icons[1] : vol <= 50 ? icons[2] : icons[3];

  return fmt
    ? snprintf(buf, len, fmt, icon, vol)
    : snprintf(buf, len, "%s", icon);
}
