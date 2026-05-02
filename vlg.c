/*
 * vtools — Vital System Utilities
 * Copyright (C) 2026 Lev Larinin
 * Licensed under GPLv3
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define KMSG "/dev/kmsg"
#define MAX_PRIO 3

int main(void) {
    int fd = open(KMSG, O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        perror(KMSG);
        return 1;
    }

    char buf[1024];
    printf("%-8s %s\n", "PRIO", "KERNEL MESSAGE (CRIT)");

    ssize_t n;
    while ((n = read(fd, buf, sizeof(buf) - 1)) > 0) {
        buf[n] = '\0'; 

        int p;
        if (sscanf(buf, "%d,", &p) != 1) continue;
        if (p > MAX_PRIO) continue;

        char *m = strchr(buf, ';');
        if (!m) continue;

        printf("%-8d %s", p, m + 1);
    }

    close(fd);
    return 0;
}
