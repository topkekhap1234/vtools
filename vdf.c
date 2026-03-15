/*
 * vtools — Vital System Utilities
 * Copyright (C) 2024 LevLarinin
 * Licensed under GPLv3
 */
 #include <stdio.h>
#include <sys/statvfs.h>

int main() {
    struct statvfs ds;
    if (statvfs("/", &ds) != 0) {
      perror("statvfs error");
      return 1;
    }

    unsigned long total = (ds.f_blocks * ds.f_frsize) / (1024 * 1024);
    unsigned long free = (ds.f_bfree * ds.f_frsize) / (1024 * 1024);
    double usage = 100.0 - ((double)ds.f_bfree / ds.f_blocks * 100.0);

    printf("Disk /: %luMB free of %luMB (%.1f%% used) ",
	   free, total, usage);
  
    if (usage > 90.0) printf("[CRITICAL]
"); else printf("[OK]
");
    return 0;
}
