#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <signal.h>

int main(){
    char tmp[10] = {0};
    FILE *getPID;

    getPID = popen("pidof /home/xhazimix/Documents/sisop/prak2/soal5", "r");
    fgets(tmp, 10, getPID);
    pid_t pid = strtoul(tmp, NULL, 10);
    pclose(getPID);
    printf("%d\n", pid);
    kill(pid, SIGKILL);
    if(kill(pid, SIGKILL) == 0) printf("Successfully killed.");
}
