#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    	struct stat info;
	    stat("/home/ah/hatiku/elen.ku",&info);
	    if(!strcmp(getpwuid(info.st_uid)->pw_name,"www-data") && !strcmp(getgrgid(info.st_gid)->gr_name,"www-data")){
		    chmod("/home/ah/hatiku/elen.ku", 0777);
    		remove("/home/ah/hatiku/elen.ku");
	}
sleep(3);
  }

  exit(EXIT_SUCCESS);
}
