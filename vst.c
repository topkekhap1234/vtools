/*
 * vtools — Vital System Utilities
 * Copyright (C) 2024 LevLarinin
 * Licensed under GPLv3
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>

int main() {
  struct sysinfo info;

  if (sysinfo(&info) != 0) {
    perror("sysinfo error");
    return 1;
  }

  const long megabyte = 1024 * 1024;

  long days = info.uptime / 86400;
    long hours = (info.uptime % 86400) / 3600;
    long mins = (info.uptime % 3600) / 60;
    printf("Uptime:   %ldd %ldh %ldm\n", days, hours, mins);

  unsigned long total_ram = (info.totalram * info.mem_unit) / megabyte;
    unsigned long free_ram = (info.freeram * info.mem_unit) / megabyte;
    printf("RAM:      %lu MB free / %lu MB total\n", free_ram, total_ram);

  printf("Load Avg: 1m: %.2f, 5m: %.2f, 15m: %.2f\n", 
            info.loads[0] / 65536.0, 
            info.loads[1] / 65536.0, 
         info.loads[2] / 65536.0);

  printf("Procs:    %d running", info.procs);

    return 0;
}
