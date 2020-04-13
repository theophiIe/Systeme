#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void *print_string(void *arg)
{
	char *str = (char *) arg;
	
	printf("%s\n", str);
	return NULL;
}

int main()
{
	pthread_t tid;
	
	pthread_create(&tid, NULL, print_string, "Hello world!");
	pthread_join(tid, NULL);
}
