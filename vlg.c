/*
 * vtools — Vital System Utilities
 * Copyright (C) 2026 LevLarinin
 * Licensed under GPLv3
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("/dev/kmsg", O_RDONLY | O_NONBLOCK);
    if (fd < 0) {
        perror("Can't access /dev/kmsg (try sudo)");
        return 1;
    }

    char buf[1024];
    printf("%-10s %s\n", "PRIO", "KERNEL LOG MESSAGE (CRITICAL ONLY)");

    while (read(fd, buf, sizeof(buf)) > 0) {
        int prio;
        char *msg;
        
        if (sscanf(buf, "%d,", &prio) == 1) {
            if (prio <= 3) {
                msg = strchr(buf, ';');
                if (msg) {
                    msg++;
                    printf("[PRIO %d] %s", prio, msg);
                }
            }
        }
        memset(buf, 0, sizeof(buf));
    }

    close(fd);
    return 0;
}
