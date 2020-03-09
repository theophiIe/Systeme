#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv)
{
	pid_t p;
	int val;
	int status;
	srand(time(NULL));
	p = fork();
	
	//PERE
	if(p)
	{
		printf("Hello Worl!d\n");
		printf("Mon pid est : %d\n", getpid());
		
		wait(&status);
		printf("\nnbre random du fils : %d\n\n", WEXITSTATUS(status)); 
	}
	
	//FILS
	else
	{
		printf("\nHello Worl!d\n");
		printf("Mon pid est : %d  |  Le pid de mon père est : %d\n", getpid(), getppid());
		val = rand() % 51;
		printf("nbre random : %d\n", val);
		exit(val);
	}
	
	exit(0);
}
