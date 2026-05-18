#define _DEFAULT_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    FILE *f = fopen("/proc/locks", "r");
    if (!f) return 1;

    char line[256], comm[256], p_path[256];
    int last_pid = -1;
    int target_pid = (argc > 1) ? atoi(argv[1]) : 0;

    printf("%-10s %-20s %-s\n", "PID", "PROCESS", target_pid ? "LOCKED FILES" : "STATUS");

    while (fgets(line, sizeof(line), f)) {
        int pid;
        unsigned long lock_inode = 0;

    
        if (sscanf(line, "%*s %*s %*s %*s %d %*x:%*x:%lu", &pid, &lock_inode) != 2) continue;
        if (pid <= 0 || (target_pid == 0 && pid == last_pid)) continue;
        if (target_pid != 0 && pid != target_pid) continue;

        last_pid = pid;
        snprintf(p_path, sizeof(p_path), "/proc/%d/comm", pid);
        
        FILE *pf = fopen(p_path, "r");
        if (pf) {
            fgets(comm, sizeof(comm), pf);
            comm[strcspn(comm, "\n")] = 0;
            fclose(pf);

            if (target_pid) {
                char fd_dir_path[256];
                snprintf(fd_dir_path, sizeof(fd_dir_path), "/proc/%d/fd", pid);
                DIR *d = opendir(fd_dir_path);
                if (d) {
                    struct dirent *de;
                    while ((de = readdir(d))) {
                        if (de->d_name[0] == '.') continue;
                        char link_path[512], real_path[512];
                        snprintf(link_path, sizeof(link_path), "%s/%s", fd_dir_path, de->d_name);
                        
                    
                        struct stat st;
                        if (stat(link_path, &st) == 0) {

                            if (st.st_ino == lock_inode) {
                                ssize_t len = readlink(link_path, real_path, sizeof(real_path) - 1);
                                if (len != -1) {
                                    real_path[len] = '\0';
                                    printf("%-10d %-20s %s\n", pid, comm, real_path);
                                }
                            }
                        }
                    }
                    closedir(d);
                }
            } else {
                printf("%-10d %-20s [HAS LOCKS]\n", pid, comm);
            }
        }
    }
    fclose(f);
    return 0;
}
