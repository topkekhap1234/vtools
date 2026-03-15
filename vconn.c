/*
 * vtools — Vital System Utilities
 * Copyright (C) 2024 LevLarinin
 * Licensed under GPLv3
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
   FILE *fp = fopen("/proc/net/tcp", "r");
    if (!fp) { perror("Can't open /proc/net/tcp"); return 1; }

    char line[256];
    printf("%-20s %-10s
", "Remote IP (Hex)", "Status");
    printf("----------------------------------
");

    fgets(line, sizeof(line), fp);
    while (fgets(line, sizeof(line), fp)) {
        char rem_addr[128];
        int state;
        sscanf(line, "%*d: %*x:%*x %[^:]:%*x %x", rem_addr, &state);
        
        if (state == 1) {
            printf("%-20s Established
", rem_addr);
        }
    }
    fclose(fp);
}
