/*
 * vtools — Vital System Utilities
 * Copyright (C) 2024 LevLarinin
 * Licensed under GPLv3
 */

 #include <stdio.h>
#include <sys/statvfs.h>

#define MOUNT "/"
#define LIMIT 90.0

int main(void) {
    struct statvfs s;
    if (statvfs(MOUNT, &s) != 0) {
        perror("statvfs error");
        return 1;
    }

    unsigned long tot = (s.f_blocks * s.f_frsize) / 1024 / 1024;
    unsigned long avl = (s.f_bavail * s.f_frsize) / 1024 / 1024;
    double use = 100.0 - ((double)s.f_bavail / s.f_blocks * 100.0);

    printf("%-10s %-10s %-10s %-10s %-10s\n", "MOUNT", "TOTAL_MB", "FREE_MB", "USED_%", "STATUS");

    printf("%-10s %-10lu %-10lu %-10.1f ", MOUNT, tot, avl, use);

    if (use > LIMIT) {
        printf("%-10s\n", "CRITICAL");
        return 0;
    }

    printf("%-10s\n", "OK");
    return 0;
}
