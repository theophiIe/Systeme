#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv)
{	
	pid_t pid = fork();
	
	if(!pid)
	{
		for(int cmpt=0; cmpt<=4; cmpt++)
		{
			sleep(1);
			printf("Je compte : %d\n", cmpt+1);
		}
		
		exit(0);
	}

	sleep(4);
	kill(pid, SIGSTOP);
	printf("On met en pause le processus fils\n");
	sleep(5);
	kill(pid, SIGCONT);
	printf("On relance le processus fils\n");
	wait(NULL);
	

	exit(0);
}
