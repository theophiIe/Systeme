#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void *print_string(void *arg)
{
	char *str = (char *) arg;
	
	printf("%s\n", str);
	return NULL;
}

void gestion_thread(void *(*start_routine) (void *), void *arg)
{
	pthread_t tid;
	
	pthread_create(&tid, NULL, start_routine, arg);
	pthread_join(tid, NULL);
}

int main()
{
	gestion_thread(print_string, "Hello world!");
	
	return 0;
}
