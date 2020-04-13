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

typedef struct 
{
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

typedef struct 
{
	pthread_t tid;
	
	int *tab;
	int taille_tab;
	int average;
} thread_struct_tab;

void *print_average_tab(void *arg)
{
	thread_struct_tab *tst = (thread_struct_tab *) arg;
	
	for(int i = 0; i < tst -> taille_tab; i++)
	{
		tst -> average += tst -> tab[i];
	}
	
	tst -> average = (tst -> average) / 5;
	
	pthread_exit(NULL);
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
	
	//	xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  //
		ta = gestion_thread_struct(ta, print_alea_int2);
	//							OU 							 //
	//~ pthread_create(&ta.tid, NULL, print_alea_int2, &ta); //
	//~ pthread_join(ta.tid, NULL);						   	 //
	//	xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  //
	
	printf("Valeur de sortie alea int : %d\n", ta.tret);
	
	//Question 1.4
	int case_tab;
	thread_struct_tab tst;
	
	tst.taille_tab = 5;
	tst.average    = 0;
	tst.tab = malloc(tst.taille_tab * sizeof(int));
	
	printf("element du tab : ");
	for(int i = 0; i< tst.taille_tab; i++)
	{
		case_tab = rand() % (100 * (i + 1));
		tst.tab[i] = case_tab;
		
		printf("%d ", tst.tab[i]);
	}
	printf("\n");
	
	pthread_create(&tst.tid, NULL, print_average_tab, &tst);
	pthread_join(tst.tid, NULL);
	
	printf("La moyenne du tableau est : %d\n", tst.average);
	
	free(tst.tab);
	
	//Question 1.5
	
	thread_struct_tab ts_t;
	
	int alea_taille = rand() % 10;
	
	ts_t.taille_tab = alea_taille;
	ts_t.average    = 0;
	ts_t.tab = malloc(ts_t.taille_tab * sizeof(int));
	
	printf("element du tab : ");
	for(int i = 0; i< ts_t.taille_tab; i++)
	{
		case_tab = rand() % (100 * (i + 1));
		ts_t.tab[i] = case_tab;
		
		printf("%d ", ts_t.tab[i]);
	}
	printf("\n");
	
	pthread_create(&ts_t.tid, NULL, print_average_tab, &ts_t);
	pthread_join(ts_t.tid, NULL);
	
	printf("La moyenne du tableau est : %d\n", ts_t.average);
	
	free(ts_t.tab);
	
	return 0;
}
