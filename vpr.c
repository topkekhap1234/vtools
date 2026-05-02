/*
 * vtools — Vital System Utilities
 * Copyright (C) 2026 LevLarinin
 * Licensed under GPLv3
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) { printf("Usage: %s <pid>\n", argv[0]); return 1; }
    
    char path[256];
    snprintf(path, sizeof(path), "/proc/%s", argv[1]);
    
    if (access(path, F_OK) == 0) {
        printf("Process PID %s is RUNNING\n", argv[1]);
    } else {
        printf("Process PID %s NOT FOUND\n", argv[1]);
    }
    return 0;
}
