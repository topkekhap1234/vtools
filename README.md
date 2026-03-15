# vtools — Lightweight System Admin Toolkit (C / POSIX)

A collection of minimalist C utilities designed for high-load system administration and incident response. 
These tools bypass heavy-weight dependencies and query the Linux kernel directly via `/proc` and system calls.

## Why vtools?
When a server is under heavy load or a DDoS attack, standard tools like `top`, `lsof`, or `netstat` can become sluggish. **vtools** are designed to be fast, static-ready, and ultra-lightweight.

## Tools Overview
- **vstat** — Instant system heartbeat (Uptime, RAM, LoadAvg).
- **vdf** — Critical disk space monitoring for the root partition.
- **vport** — Fast TCP port availability check (no-nmap required).
- **vtop** — Instant snapshot of the Top-5 most resource-heavy processes.
- **vconn** — Active TCP connection counter (DDoS detection).
- **vfiles** — Identifies processes with potential file descriptor leaks.
- **vlock** — Locates processes currently holding file locks.
- **vlog** — Real-time log scanner with color-coded error highlighting.

## Build & Install
Designed for **Void Linux**, but compatible with any POSIX system (glibc/musl).

```bash
make
sudo make install
