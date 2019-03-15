#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int main(){
    pid_t pid, sid;
    pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);

    umask(0);
    sid = setsid();
    if (sid < 0) exit(EXIT_FAILURE);

    if ((chdir("/home/xhazimix/Documents/")) < 0) exit(EXIT_FAILURE);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while(1){
        char folder[50];
        char dir[100] = "/home/xhazimix/Documents/log/";
        time_t t = time(NULL);
	struct tm current = *localtime(&t);
        FILE *syslog;
	sprintf(folder,"%d:%d:%d-%d:%d", current.tm_mday, current.tm_mon+1, current.tm_year+1900, current.tm_hour, current.tm_min);
        strcat(dir, folder);
        mkdir(dir, 0777);
	int i = 0;
        while(i < 30){
            syslog = fopen("/var/log/syslog", "r");
            char file[100];
            char c;
            FILE *logbaru;
	    i++;
            sprintf(file, "%s/log%d.log", dir, i);
            logbaru = fopen(file, "w");
            while(fscanf(syslog, "%c", &c) != EOF) fprintf(logbaru, "%c", c);
            fclose(logbaru);
            fclose(syslog);
            sleep(60);
        }
    }
    exit(EXIT_SUCCESS);
}
