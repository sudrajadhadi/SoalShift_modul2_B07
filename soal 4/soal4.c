#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <sys/sysmacros.h>
#include <string>

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
  int counter=1;
  while(1) {
	   struct stat info_file;
	   char file_makan_enak[]="/home/its_time_to/Documents/file_makan_enak.txt";
	   stat(file_makan_enak,&info_file);
	   time_t now; time(&now);
	   int dif = difftime(now, info_file.st_atime); 
	   if(dif<=30){ 
	   	char path[150],str[20];
		strcpy(path, "/home/its_time_to/Documents/makan");
	     	sprintf(str,"_sehat%d.txt",counter );
	     	strcat(path,str);
	     	FILE *baru;
	    	baru = fopen(path,"w");
	     	fclose(baru);
	     	counter ++;
	     	sleep(5);
	     	}
  }
  exit(EXIT_SUCCESS);
}
