#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/times.h>

void aff_rep(char *path, struct tms buf)
{
	sleep(2);
	times(&buf);
	execlp("ls", "ls", path, "-R", NULL);
}

int main(int argc, char **argv)
{
	struct tms buf;
	int status;
	
	if(!fork())
		aff_rep("/home/user", buf);
	
	wait(&status);
	
	times(&buf);
	printf("Temps d'excution : %f\n", (float)( (buf.tms_cutime + buf.tms_cstime) / (sysconf(_SC_CLK_TCK) )));

	exit(0);
}
