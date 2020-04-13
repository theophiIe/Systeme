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
	pthread_exit(NULL);
}

void *print_alea_int(void *arg)
{
	int *alea = (int *) arg;
	
	printf("alea int : %d\n", *alea);
	pthread_exit(NULL);
}

void gestion_thread(void *(*start_routine) (void *), void *arg)
{
	pthread_t tid;
	
	pthread_create(&tid, NULL, start_routine, arg);
	pthread_join(tid, NULL);
}

typedef struct {

  //Thread ID
  pthread_t tid;

  //Thread argument/parameter
  int targ;

  //Thread return value
  int tret;

} thread_arg_t;

void *print_alea_int2(void *arg)
{
	thread_arg_t *alea = (thread_arg_t *) arg;
	
	alea -> tret = rand() % alea -> targ;
	
	printf("alea : %d\n", alea -> tret);
	
	pthread_exit(NULL);
}

thread_arg_t gestion_thread_struct(thread_arg_t ta, void *(*start_routine) (void *))
{
	pthread_create(&ta.tid, NULL, start_routine, &ta);
	pthread_join(ta.tid, NULL);
	
	return ta;
}

int main()
{
	//Question 1.1
	gestion_thread(print_string, "Hello world!");
	
	//Question 1.2
	srand(getpid());
	
	int alea = rand() % 100;
	gestion_thread(print_alea_int,  &alea);
	
	//Question 1.3
	thread_arg_t ta;
	
	ta.targ = 10;
	ta.tret = 0;
	
	ta = gestion_thread_struct(ta, print_alea_int2);
	
	//~ pthread_create(&ta.tid, NULL, print_alea_int2, &ta);
	//~ pthread_join(ta.tid, NULL);

	printf("Valeur de sortie alea int : %d\n", ta.tret);
	
	return 0;
}
