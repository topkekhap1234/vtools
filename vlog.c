/*
 * vtools — Vital System Utilities
 * Copyright (C) 2024 LevLarinin
 * Licensed under GPLv3
 */
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) { 
        printf("Usage: %s <logfile>
", argv[0]); 
        return 1; 
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
      perror("File error");
      return 1;
    }

    char line[1024];
    printf("--- Scanning %s for issues ---
", argv[1]);

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "ERROR") || strstr(line, "FAIL") || strstr(line, "crit")) {
            // [1;31m — FAT RED COLOR
            printf("[1;31m[!] %s[0m", line);
        }
    }

    fclose(fp);
    return 0;
}
