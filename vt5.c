/*
 * vtools — Vital System Utilities
 * Copyright (C) 2026 LevLarinin
 * Licensed under GPLv3
 */
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int pid;
    char name[512];
    unsigned long utime;
} Proc;

int cmp(const void *a, const void *b) {
    return ((Proc*)b)->utime - ((Proc*)a)->utime;
}

int main() {
    DIR *dir = opendir("/proc");
    if (!dir) return 1;

    Proc p[1024];
    int n = 0;
    struct dirent *e;

    while ((e = readdir(dir)) && n < 1024) {
        if (!isdigit(e->d_name[0])) continue;

        char path[512];
        snprintf(path, sizeof(path), "/proc/%s/stat", e->d_name);
        
        FILE *f = fopen(path, "r");
        if (f) {
            fscanf(f, "%d (%[^)]) %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu", 
                   &p[n].pid, p[n].name, &p[n].utime);
            fclose(f);
            n++;
        }
    }
    closedir(dir);

    qsort(p, n, sizeof(Proc), cmp);

    printf("%-8s %-20s %-10s\n", "PID", "NAME", "TICKS");
    for (int i = 0; i < (n < 5 ? n : 5); i++) {
        printf("%-8d %-20s %-10lu\n", p[i].pid, p[i].name, p[i].utime);
    }

    return 0;
}
