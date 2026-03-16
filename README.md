# vtools — Vital System Admin Toolkit (C / POSIX)

**vtools** is a collection of minimalist C utilities designed for high-pressure system administration and emergency incident response. When a server is under heavy load or a DDoS attack, standard heavy-weight tools can become sluggish. **vtools** bypass high-level dependencies by querying the Linux kernel directly via `/proc` and low-level system calls.

### The "Vital" Philosophy
Every tool starts with the **v** (Vital) prefix and follows a "three-letter" mnemonic. This ensures commands are ultra-short and easy to type during critical server outages.

### Tools Overview


| Command | Name | Description |
|:---|:---|:---|
| **`vst`** | Vital STatus | Instant system heartbeat: Uptime, RAM, and Load Average. |
| **`vfs`** | Vital File System | High-speed monitoring of root partition space. |
| **`vpt`** | Vital PorTs | Rapid TCP port availability check (no nmap required). |
| **`vt5`** | Vital Top 5 | Snapshot of the Top-5 most resource-heavy processes. |
| **`vpr`** | Vital PRocess | Check if a specific PID is currently running. |
| **`vcn`** | Vital ConNections | Active TCP connection monitor for DDoS detection. |
| **`vfl`** | Vital FiLes | Identifies processes with potential file descriptor leaks. |
| **`vlk`** | Vital LocKs | Locates processes currently holding critical file locks. |
| **`vlg`** | Vital LoGs | Emergency kernel log scanner (Errors/Critical only). |

### Build & Install
Designed for **Linux** (musl/glibc), but fully compatible with any POSIX-compliant system.

```bash
# Clone the repository
git clone https://github.com/topkekhap1234/vtools
cd vtools

# Build and install
make
sudo make install
```
