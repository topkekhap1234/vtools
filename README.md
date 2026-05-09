# vtools: Vital System Admin Toolkit

vtools is a collection of minimalist C utilities designed for high-pressure system administration and emergency incident response.
When a server is under heavy load, experiencing a DDoS attack, or running out of memory, standard tools like top, lsof, or netstat can become sluggish or fail. vtools bypasses high-level dependencies by querying the Linux kernel directly via /proc and low-level system calls, ensuring they remain responsive even in critical situations.
------------------------------
# Design Philosophy

* Zero Dependencies: Built using pure C and POSIX-compliant headers.
* Minimal Footprint: Extremely low CPU and RAM usage.
* Mnemonic Commands: All tools use a 3-letter prefix starting with "v" (Vital) for rapid typing during outages.

------------------------------
# Tools Overview

| Command | Name | Description |
|---|---|---|
| vst | Vital STatus | Instant system heartbeat: Uptime, RAM, and Load Average. |
| vfs | Vital File System | High-speed monitoring of root partition disk space and inodes. |
| vpt | Vital PorTs | Rapid check of open TCP ports without external dependencies. |
| vt5 | Vital Top 5 | A snapshot of the five most resource-heavy processes. |
| vpr | Vital PRocess | Verifies if a specific PID is currently active. |
| vcn | Vital CoNnections | Active TCP connection monitor for DDoS detection. |
| vfl | Vital FiLes | Identifies processes with potential file descriptor leaks. |
| vlk | Vital LocKs | Locates processes holding critical file locks. |
| vlg | Vital LoGs | Emergency kernel log scanner filtering for Errors and Critical events. |

------------------------------
# Installation Prerequisites

To build the toolkit, you need a C compiler (gcc) and make. On Debian-based systems, these are included in the build-essential package.
## Build and Install
```bash
# Clone the repository
git clone https://github.com/topkekhap1234/vtools
cd vtools
# Compile the source code
make
# Install binaries to /usr/local/bin
sudo make install
```
## Uninstallation
```bash
sudo make uninstall
```
------------------------------
# Usage Examples

* Quick Health Check:
Run vst to see the current load and available memory.
* DDoS Investigation:
Run vcn to monitor incoming network connections in real-time.
* Performance Bottlenecks:
Run vt5 to identify which processes are consuming the most CPU/RAM.

------------------------------
# License

This project is licensed under the GPL-3.0 License. See the LICENSE file for details.
------------------------------
