/*
 * vtools — Vital System Utilities
 * Copyright (C) 2024 LevLarinin
 * Licensed under GPLv3
 */
#include <stdio.h>
#include <string.h>

int main() {
    FILE *f = fopen("/proc/locks", "r");
    if (!f) return 1;

    char line[256], comm[256], p_path[256];
    int last_pid = -1;

    printf("%-10s %-20s %-s\n", "PID", "PROCESS", "STATUS");

    while (fgets(line, sizeof(line), f)) {
        int pid;
        if (sscanf(line, "%*d: %*s %*s %*s %d", &pid) != 1) continue;
        if (pid == last_pid || pid <= 0) continue;

        last_pid = pid;
        snprintf(p_path, sizeof(p_path), "/proc/%d/comm", pid);
        
        FILE *pf = fopen(p_path, "r");
        if (pf) {
            fgets(comm, sizeof(comm), pf);
            comm[strcspn(comm, "\n")] = 0;
            fclose(pf);
            printf("%-10d %-20s [HAS LOCKS]\n", pid, comm);
        }
    }
    fclose(f);
    return 0;
}
