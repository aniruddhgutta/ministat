#include <stdio.h>
#include <string.h>
#include <dirent.h>

int
bluetooth(char *buf, size_t len, const char *arg)
{
	DIR *d;
	struct dirent *de;
	char path[64], line[16];
	FILE *fp;

	d = opendir("/proc");
	if (!d) return snprintf(buf, len, "󰂲");
	
	while ((de = readdir(d))) {
		if (de->d_name[0] < '0') continue;
		snprintf(path, sizeof(path), "/proc/%s/comm", de->d_name);
		fp = fopen(path, "r");
		if (fp && fgets(line, sizeof(line), fp) && !strncmp(line, "bluetoothd", 10)) {
			fclose(fp);
			break;
		}
		if (fp) fclose(fp);
	}
	closedir(d);
	if (!de) return snprintf(buf, len, "󰂲");

	d = opendir("/sys/class/bluetooth/hci0");
	if (!d) return snprintf(buf, len, "󰂯");
	while ((de = readdir(d)))
		if (strchr(de->d_name, ':'))
			break;
	closedir(d);
	return snprintf(buf, len, de ? "󰂱" : "󰂯");
}
