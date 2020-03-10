#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

void aff_rep(char *path)
{
	execlp("ls", "ls", path, "-R", NULL);
}

int main(int argc, char **argv)
{
	time_t timeBefore = time(NULL);
	
	if(!fork())
	{
		sleep(2);
		aff_rep("/home/user");
		exit(0);
	}

	
	wait(NULL);
	
	time_t timeAfter = time(NULL);
	printf("Temps d'excution : %ld\n", timeAfter-timeBefore);

	exit(0);
}
