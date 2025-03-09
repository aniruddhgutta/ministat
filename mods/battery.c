#include "../minibar.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const char *icons[] = {
  "󰁺", "󰁻", "󰁼", "󰁽", "󰁾", "󰁿", "󰂀", "󰂁", "󰂂", "󰁹"
};
static const char *charging_icon = "󰂄";

int battery(char *buf, size_t len, const char *arg) {
  char path[PATH_MAX];
  int perc = 0;
  char status[32] = {0};

  snprintf(path, sizeof(path), "/sys/class/power_supply/BAT0/capacity");
  FILE *fp = fopen(path, "r");
  if (!fp || fscanf(fp, "%d", &perc) != 1) {
    if (fp) fclose(fp);
    return 0;
  }
  fclose(fp);

  snprintf(path, sizeof(path), "/sys/class/power_supply/BAT0/status");
  fp = fopen(path, "r");
  if (fp) {
    fgets(status, sizeof(status), fp);
    fclose(fp);
    status[strcspn(status, "\n")] = '\0';
  }

  int idx = perc >= 100 ? 9 : perc / 10;
  const char *icon = strstr(status, "Charging") ? charging_icon : icons[idx];

  if (strstr(status, "Charging") || strstr(status, "Discharging")) {
    snprintf(buf, len, "%s %d", icon, perc);
    return 1;
  }

  if (arg && strstr(arg, "%d")) {
    snprintf(buf, len, arg, icon, perc);
  } else {
    snprintf(buf, len, "%s", icon);
  }

  return 1;
}
