/*
 * vtools — Vital System Utilities
 * Copyright (C) 2024 LevLarinin
 * Licensed under GPLv3
 */
#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

int main() {
    DIR *d = opendir("/proc");
    struct dirent *e;
    if (!d) return 1;

    printf("%-8s %-20s %-10s\n", "PID", "NAME", "FILES");
    
    while (
    (e = readdir(d))
    ) {
        if (!isdigit(e->d_name[0])) continue;

        char path[512], buf[512];
        snprintf(path, sizeof(path), "/proc/%s/fd", e->d_name);
        
        DIR *fd_dir = opendir(path);
        if (!fd_dir) continue;

        int count = 0;
        while (readdir(fd_dir)) count++;
        closedir(fd_dir);

        if (count > 50) {
          snprintf(path, sizeof(path), "/proc/%s/comm", e->d_name);
            FILE *f = fopen(path, "r");
            fgets(buf, sizeof(buf), f);
            buf[strcspn(buf, "\n")] = 0;
            fclose(f);
            
            printf("%-8s %-20s %-10d\n", e->d_name, buf, count - 2);
        }
    }
    closedir(d);
    return 0;
}
