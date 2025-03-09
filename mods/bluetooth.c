#define _POSIX_C_SOURCE 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bluetooth(char *buf, size_t len, const char *arg) {
  FILE *fp;
  char out[256], addr[18] = "";
  const char *icon = "󰂲";

  if (!(fp = popen("pgrep bluetoothd", "r")) || !fgets(out, sizeof(out), fp)) {
    if (fp) pclose(fp);
    return snprintf(buf, len, "%s", icon);
  }
  pclose(fp);

  if (!(fp = popen("bluetoothctl show | grep 'Powered: yes'", "r")) || !fgets(out, sizeof(out), fp)) {
    if (fp) pclose(fp);
    return snprintf(buf, len, "%s", icon);
  }
  pclose(fp);

  if (!(fp = popen("bluetoothctl devices Connected | awk '{print $2}'", "r")) || !fgets(addr, sizeof(addr), fp)) {
    if (fp) pclose(fp);
    return snprintf(buf, len, "󰂯");
  }
  pclose(fp);
  addr[strcspn(addr, "\n")] = 0;

  icon = "󰂱";

  int batt = -1;
  char cmd[128];
  snprintf(cmd, sizeof(cmd), "bluetoothctl info %s | grep 'Battery' | awk -F '[()]' '{print $2}'", addr);
  if ((fp = popen(cmd, "r")) && fgets(out, sizeof(out), fp)) {
    batt = atoi(out);
  }
  if (fp) pclose(fp);

  if (batt >= 0 && (strstr(arg, "%d") || batt < 30)) {
    return snprintf(buf, len, "%s %d", icon, batt);
  }
  return snprintf(buf, len, "%s", icon);
}
