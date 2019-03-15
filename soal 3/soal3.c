#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	pid_t child_id;
	int status, to[2];

	child_id = fork();
	if (child_id == 0) execl("/usr/bin/unzip", "unzip", "campur2.zip", NULL);

	child_id = fork();
	if (child_id == 0) execlp("touch", "touch", "daftar.txt", NULL);

	while(wait(&status)>0);
	pipe(to);
	child_id = fork();

	if (child_id == 0) 
	{
		close(to[0]);
		dup2(to[1], STDOUT_FILENO);
		execlp("ls", "ls", "campur2", NULL);
	}
	close(to[1]);

	char temp[1024];
	FILE *open_ls = fdopen(to[0], "r");
	FILE *file_daftar = fopen("daftar.txt", "w");

	while (fgets(temp, sizeof(temp), open_ls) != NULL) {
		if (strstr(&temp[strlen(temp)-5], ".txt") != NULL)
			fprintf(file_daftar, "%s", temp);
	}
	fclose(file_daftar);
}
