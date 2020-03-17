#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define TAILLE_MESSAGE 16

void tubeAnonyme()
{
	int fildes[2];
	char *messageEcrire = "Hello world !";
	char messageLecture[256];
	
	if(pipe(fildes) != 0)
        fprintf(stderr, "Erreur de création du tube.\n");
    
	if(!fork())
	{
		close(fildes[0]);
		printf("Le fils ecris le message %s \n", messageEcrire);
		write(fildes[1], messageEcrire, strlen(messageEcrire));
	}	
	
	else
	{
		close(fildes[1]);
		read(fildes[0], messageLecture, 256);
		printf("Le pere reçois le message du fils : %s \n\n", messageLecture);
		wait(NULL);
	}	
}

void tubeNomme()
{
	if(mkfifo("/tmp/tube-test", 0777) != 0)
	{
		printf("Echec du mkfifo erreur lors de la création du processus\n");
		exit(1);
	}
	
	int fd = open("/tmp/tube-test", O_RDWR);
	
	if(fd < 0)	
		perror("Problème avec open ");
	
	if(!fork())
	{
		if(write(fd, "Hello World!", TAILLE_MESSAGE) < 0)	
			perror("Problème avec write ");
			
		printf("Le processus fils a écrit le message dans le tube !\n");
	}
	
	else
	{
		wait(NULL);
		char lecture[TAILLE_MESSAGE];
		read(fd, lecture, TAILLE_MESSAGE);
		printf("Le processus père reçoit le message : %s\n\n",lecture);
		close(fd);
		unlink("/tmp/tube-test");
	}
}

int main(int argc, char **argv)
{
	tubeAnonyme();
	tubeNomme();
	
	exit(0);
}
