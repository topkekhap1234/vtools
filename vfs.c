/*
 * vtools — Vital System Utilities
 * Copyright (C) 2026 LevLarinin
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
    
    // Считаем нагрузку на иноды (файловые дескрипторы)
    double i_use = 100.0 - ((double)s.f_favail / s.f_files * 100.0);
    double worst = (use > i_use) ? use : i_use;

    printf("%-10s %-10s %-10s %-10s %-10s\n", "MOUNT", "TOTAL_MB", "FREE_MB", "USED_%", "CONDITION");

    printf("%-10s %-10lu %-10lu %-10.1f ", MOUNT, tot, avl, use);

    // Логика умного CONDITION вместо STATUS
    if (worst > 98.0) {
        printf("%-10s\n", "FULL");
    } else if (worst > LIMIT) {
        printf("%-10s\n", "CRITICAL");
    } else if (worst > 75.0) {
        printf("%-10s\n", "CROWDED");
    } else if (s.f_flag & ST_RDONLY) {
        printf("%-10s\n", "READONLY");
    } else {
        printf("%-10s\n", "HEALTHY");
    }

    return 0;
}
