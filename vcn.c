/*
 * vtools — Vital System Utilities
 * Copyright (C) 2026 Lev Larinin
 * Licensed under GPLv3
 */
#include <stdio.h>
#define TCP_PATH "/proc/net/tcp"
#define ESTABLISHED 1

void printcon(const char *line) {
    char remip[64];
    int state;

    if (sscanf(line, "%*d: %*x:%*x %63[^:]:%*x %x", remip, &state) != 2)
        return;

    if (state != ESTABLISHED)
        return;

    printf("%-20s %-12s\n", remip, "ESTABLISHED");
}

int main(void) {
    FILE *f = fopen(TCP_PATH, "r");
    if (!f) return 1;

    char buf[256];
    printf("%-20s %-12s\n", "REMOTE_IP_HEX", "STATUS");

    /* Пропускаем первую строку (заголовок) */
    if (!fgets(buf, sizeof(buf), f)) {
        fclose(f);
        return 0;
    }

    /* Читаем файл до конца */
    while (fgets(buf, sizeof(buf), f))
        printcon(buf);

    fclose(f);
    return 0;
}
