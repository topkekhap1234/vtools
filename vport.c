/*
 * vtools — Vital System Utilities
 * Copyright (C) 2024 LevLarinin
 * Licensed under GPLv3
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 3) { printf("Usage: %s <ip> <port>
", argv[0]); return 1; }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = { .sin_family = AF_INET, .sin_port = htons(atoi(argv[2])) };
    inet_pton(AF_INET, argv[1], &addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == 0) {
        printf("Port %s on %s is OPEN
", argv[2], argv[1]);
        close(sock); return 0;
    } else {
        printf("Port %s on %s is CLOSED
", argv[2], argv[1]);
        return 1;
    }
}
