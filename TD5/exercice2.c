#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

/*	CETTE METHODE N'EST PAS EN PARALLELE
	while(cmpt != 10)
	{
		//PERE
		if(pid)
		{
			wait(&status);
			printf("\nPIDFILS : %d\n\n", WEXITSTATUS(status));
		}
		
		//FILS
		else
		{
			int val = rand() % 3;
			sleep(val);
			printf("pid pere : %d\n", getppid());
			exit(getpid());
		}
		
		pid = fork();
		cmpt++;
	}
*/	

int main(int argc, char **argv)
{	
	pid_t pid;
	int cmpt;
	int status;
	
	srand(time(NULL));
	
	for(cmpt=0; cmpt<10; cmpt++)
	{
		int sec = rand() % 11;
		pid = fork();
		
		if(!pid)
		{
			sleep(sec);
			printf("le processus est : %d | son processus père est : %d\n", getpid(), getppid());
			exit(0);
		}
	}
	
	for(cmpt=0; cmpt<10; cmpt++)
	{
		pid = wait(&status);
		printf("le processus fils : %d est fini\n", pid);
	}
	
	return 0;
}
