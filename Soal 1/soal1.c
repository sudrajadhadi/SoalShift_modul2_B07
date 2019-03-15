#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

int main() {
  pid_t pid, sid;
  pid = fork();
  if (pid < 0) exit(EXIT_FAILURE);
  if (pid > 0) exit(EXIT_SUCCESS);

  umask(0);
  sid = setsid();
  if (sid < 0)  exit(EXIT_FAILURE);

  if ((chdir("/home/xhazimix/Documents/")) < 0) exit(EXIT_FAILURE);

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
   DIR *directory;
    struct dirent *dir;
    directory = opendir("/home/xhazimix/Documents/");

    if (directory)
    {
        while ((dir = readdir(directory)) != NULL)
        {
	    char namafile[200];
	    int cpy = (int) strlen(dir->d_name);
	    char *nama = dir->d_name;
	    if(nama[cpy-4] == '.' && nama[cpy-3]=='p' && nama[cpy-2]=='n' && nama[cpy-1] == 'g'){
		printf("%s %d\n", dir->d_name, (int) strlen(dir->d_name));
		strcpy(namafile, "/home/xhazimix/modul2/gambar/");
		strcat(namafile, nama);
		cpy = (int)strlen(namafile);
		namafile[cpy-4] = '\0';
		strcat(namafile, "_grey.png");
		if (fork() == 0){
			char *argv[] = {"mv", nama, namafile, NULL};
			execv("/bin/mv", argv);
		}
		printf("%s\n", namafile);
            }
        }
        closedir(directory);
    }
    sleep(10);
  } 
  exit(EXIT_SUCCESS);
}
