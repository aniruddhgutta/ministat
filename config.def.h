#include "ministat.h"

static const struct arg {
    int (*func)(char *, size_t, const char *);
    const char *fmt;
    const char *arg;
} 

args[] = {
    /* function       format          argument */
    { shell,          "  %s  |",      "media -s" },
    { network,        "  %s",         "wlan0" },    /* wlp4s0 */
    { battery,        "  %s",         NULL },
    { volume,         "  %s  |",      "Master" },
    { ram,            "  %sMi",       NULL },
    { temp,           "  %sC",        "hwmon4" },   /* hwmon5 */
    { cpu,            "  %s  |",      NULL },
    { datetime,       "  %s ",        "%b %d, %H:%M" },
};
