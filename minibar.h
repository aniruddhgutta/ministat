#ifndef MINIBAR_H
#define MINIBAR_H

#include <stddef.h>  /* For size_t */
#include <stdio.h>   /* For snprintf */
#include <linux/limits.h> /* For PATH_MAX */

int datetime(char *buf, size_t len, const char *fmt);
int battery(char *buf, size_t len, const char *fmt);
int ram(char *buf, size_t len, const char *fmt);
int temp(char *buf, size_t len, const char *fmt);
int cpu(char *buf, size_t len, const char *arg);
int network(char *buf, size_t len, const char *arg);
int volume(char *str, size_t size, const char *fmt);
int bluetooth(char *str, size_t size, const char *arg);
int shell(char *buf, size_t len, const char *script);

#endif /* MINIBAR_H */
