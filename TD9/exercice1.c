#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

void *print_string(void *arg)
{
	char *str = (char *) arg;
	
	printf("message : %s\n", str);
	pthread_exit( NULL );
}

void *print_alea_int(void *arg)
{
	int *alea = (int *) arg;
	
	printf("alea int : %d\n", *alea);
	pthread_exit( NULL );
}

void gestion_thread(void *(*start_routine) (void *), void *arg)
{
	pthread_t tid;
	
	pthread_create(&tid, NULL, start_routine, arg);
	pthread_join(tid, NULL);
}

int main()
{
	//Question 1.1
	gestion_thread(print_string, "Hello world!");
	
	//Question 1.2
	srand(getpid());
	
	int alea = rand() % 100;
	gestion_thread(print_alea_int,  &alea);
	
	return 0;
}
