#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

void excution(int cmpt)
{
	switch (cmpt)
	{
		case 0:
			execl("/bin/ps", "ps" , NULL);
			break;
			
		case 1:
			execlp("ls", "ls", "/home/user", NULL);
			break;
			
		case 2:
			execlp("find", "find", "/home/user/Bureau", "-type" ,"d", NULL);
			break;
			
		case 3:
			execlp("find", "find", "/home/user/Bureau", "-type" ,"f", NULL);
			break;
			
		default:
			printf("Processus inutile");
			break;
	}
}

int main(int argc, char **argv)
{
	int status;
	pid_t pid;
	
	for(int cmpt=0; cmpt<=3; cmpt++)
	{
		pid = fork();
		
		if(!pid)
		{
			excution(cmpt);
			exit(0);
		}
	}
	
	for(int cmpt=0; cmpt<=3; cmpt++)
	{
		pid = wait(&status);
		printf("le processus fils : %d est fini\n", pid);
	}
	exit(0);
}

