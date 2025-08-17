#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "config.h"

#define LEN(x) (sizeof(x) / sizeof(*(x)))
#define SIGSTATUS SIGRTMIN

volatile sig_atomic_t reload = 1;

void sighandler(int sig) {
    reload = 1;
}

void print_status(void) {
    char buf[1024] = {0}, out[256];
    for (size_t i = 0; i < LEN(args); i++) {
        if (args[i].func(out, sizeof(out), args[i].arg)) {
            snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf), args[i].fmt, out);
        }
    }
    printf("%s\n", buf);
    fflush(stdout);
}

int main(void) {
    signal(SIGSTATUS, sighandler);

    while (1) {
        if (reload) {
            print_status();
            reload = 0;
        }
        sleep(1);
        print_status();
    }
    return 0;
}
