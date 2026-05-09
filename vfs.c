/*
 * vtools — Vital System Utilities
 * Copyright (C) 2026 LevLarinin
 * Licensed under GPLv3
 */

#include <stdio.h>
#include <sys/statvfs.h>

#define MOUNT "/"

int main(void) {
    struct statvfs s;
    if (statvfs(MOUNT, &s) != 0) {
        perror("root error");
        return 1;
    }

    double use = 100.0 - ((double)s.f_bavail / s.f_blocks * 100.0);    
    double i_use = 100.0 - ((double)s.f_favail / s.f_files * 100.0);

    printf("%-10s %-10s %-10s\n", "MOUNT",  "USED_MEM%", "USED_INODES_%");

    printf("%-10s %-10.1f %-10.1f\n", MOUNT, use, i_use);

    return 0;
}
