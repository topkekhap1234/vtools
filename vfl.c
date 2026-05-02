/*
 * vtools — Vital System Utilities
 * Copyright (C) 2026 Lev Larinin
 * Licensed under GPLv3
 */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

#define PROC "/proc"

void getname(const char *pid, char *buf, size_t sz) {
    char path[512];
    snprintf(path, sizeof(path), PROC "/%s/comm", pid);
    
    FILE *f = fopen(path, "r");
    if (!f) {
        strncpy(buf, "unknown", sz);
        return;
    }

    if (fgets(buf, sz, f)) 
        buf[strcspn(buf, "\n")] = '\0';

    fclose(f);
}

int cntfds(const char *pid) {
    char path[512];
    snprintf(path, sizeof(path), PROC "/%s/fd", pid);
    
    DIR *d = opendir(path);
    if (!d) return -1;

    int n = 0;
    struct dirent *e;
    while ((e = readdir(d)))
        if (e->d_name[0] != '.') n++;

    closedir(d);
    return n;
}

int main(int argc, char *argv[]) {
    int thr = (argc > 1) ? atoi(argv[1]) : 200;
    DIR *pd = opendir(PROC);
    if (!pd) return 1;

    printf("%-8s %-20s %-10s\n", "PID", "NAME", "FD_CNT");

    struct dirent *ent;
    while ((ent = readdir(pd))) {
        if (!isdigit(ent->d_name[0])) continue;

        int num = cntfds(ent->d_name);
        if (num < thr) continue;

        char name[256];
        getname(ent->d_name, name, sizeof(name));
        printf("%-8s %-20s %-10d\n", ent->d_name, name, num);
    }

    closedir(pd);
    return 0;
}
