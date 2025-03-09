#include "minibar.h"

static const struct arg {
    int (*func)(char *, size_t, const char *);
    const char *fmt;
    const char *arg;
} 
args[] = {
    /* function       format          argument */
/*  { shell,          "  %s  |",      "tomato -t" }, */
    { shell,          "  %s  |",      "media -s" },
    { network,        "  %s",         "wlp4s0" },
/*  { bluetooth,      "  %s",         NULL }, */
    { volume,         "  %s",         NULL },
    { battery,        "  %s  |",      NULL },
/*  { temp,           "  %s℃ ",       "hwmon5" }, */
/*  { cpu,            " %s%%",        NULL }, */
/*  { ram,            "  %sMi  |",    NULL }, */
    { datetime,       "  %s ",        "%b %d, %H:%M" },
};
