/*
 * vtools — Vital System Utilities
 * Copyright (C) 2026 LevLarinin
 * Licensed under GPLv3
 */
#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int threshold = (argc > 1) ? atoi(argv[1]) : 200;
    
    DIR *d = opendir("/proc");
    struct dirent *e;
    if (!d) {
        perror("opendir /proc");
        return 1;
    }

    printf("%-8s %-20s %-10s\n", "PID", "NAME", "FD_COUNT");

    while ((e = readdir(d))) {
        if (!isdigit(e->d_name[0])) continue;

        char path[512], buf[512];
        snprintf(path, sizeof(path), "/proc/%s/fd", e->d_name);
        
        DIR *fd_dir = opendir(path);
        if (!fd_dir) continue;

        int count = 0;
        while (readdir(fd_dir)) count++;
        closedir(fd_dir);

        count -= 2;

        if (count >= threshold) {
            snprintf(path, sizeof(path), "/proc/%s/comm", e->d_name);
            FILE *f = fopen(path, "r");
            if (f) {
                if (fgets(buf, sizeof(buf), f)) {
                    buf[strcspn(buf, "\n")] = 0;
                }
                fclose(f);
            } else {
                strncpy(buf, "unknown", sizeof(buf));
            }
            
            printf("%-8s %-20s %-10d\n", e->d_name, buf, count);
        }
    }
    closedir(d);
    return 0;
}
