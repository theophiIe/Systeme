#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct 
{
	int nbThreads;			//< Nombre de threads à utiliser
	int tailleTableau;		//< Taille du tableau
	
} arg_t;

typedef struct 
{
	pthread_mutex_t   *mut;
	pthread_barrier_t *bar;
	pthread_t tid;
	
	int *tab;
	int start;
	int end;
	int *res;
	
} message_t;

void * sommeTableauMut (void * arg)
{
	message_t *mt = (message_t *) arg;

	for(int i = mt -> start; i < mt -> end; i++)
	{
		pthread_mutex_lock(mt -> mut);
		*(mt -> res) += mt -> tab[i];
		pthread_mutex_unlock(mt -> mut);
	}
	
	printf("Fin du calcul pour le thread mut n°%ld\n", mt -> tid);
	
	return NULL;
}

void * sommeTableauBar (void * arg)
{
	message_t *mt = (message_t *) arg;
	
	if(pthread_barrier_wait(mt -> bar))
		printf("Le thread n°%ld n'est plus bloqué\n", mt -> tid);
	
	for(int i = mt -> start; i < mt -> end; i++)
		*(mt -> res) += mt -> tab[i];

	printf("Fin du calcul pour le thread bar n°%ld\n", mt -> tid);
	
	return NULL;
}

void * sommeTableau (void * arg)
{
	message_t *mt = (message_t *) arg;
	
	if(pthread_barrier_wait(mt -> bar))
		printf("Le thread n°%ld n'est plus bloqué\n", mt -> tid);
	
	for(int i = mt -> start; i < mt -> end; i++)
	{
		pthread_mutex_lock(mt -> mut);
		*(mt -> res) += mt -> tab[i];
		pthread_mutex_unlock(mt -> mut);
	}
	
	printf("Fin du calcul pour le thread n°%ld\n", mt -> tid);
	
	return NULL;
}

arg_t analyseArguments (int argc, char ** argv)
{
	printf("nbre d'arg %d\n", argc);
	
	if(argc != 3)
	{
		printf("Erreur, nombre d'argument non valide\n");
		exit(EXIT_FAILURE);
	}
	
	arg_t at;
	
	at.nbThreads = atoi(argv[1]);
	printf("Le nombre de thread est de : %d\n", at.nbThreads);
	
	at.tailleTableau = atoi(argv[2]);
	printf("Le taille du tableau est de : %d\n", at.tailleTableau);
		
	return at;
}

int * genereTableau (int tailleTableau)
{
	int *tab = malloc(tailleTableau * sizeof(int));
	
	printf("Le tableau contient : ");
	for(int i = 0; i < tailleTableau; i++)
	{
		tab[i] = rand() % 100;
		printf("%d ", tab[i]);
	}
	printf("\n");
	
	return tab;
}

void programmePrincipalMut (const arg_t arg)
{
	//Déclaration des variables 
	pthread_mutex_t   mut;

	message_t *mt;
	
	int *tab;
	int res = 0;
	int dec = arg.tailleTableau/arg.nbThreads;
	
	//Allocation de la mémoire
	tab 	= genereTableau (arg.tailleTableau);
	mt 		= malloc(arg.nbThreads * sizeof(message_t));
	
	pthread_mutex_init(&mut, NULL);
	
	//Création des threads
	for(int i = 0; i < arg.nbThreads; i++)
	{
		mt[i].start = i*dec;
		mt[i].end   = i*dec + dec;
		mt[i].tab	= tab;
		mt[i].mut	= &mut;
		mt[i].res	= &res;
	}
	
	//Thread pour mutex
	for(int i = 0; i < arg.nbThreads; i++)
		pthread_create(&mt[i].tid, NULL, sommeTableauMut, &mt[i]);
	
	for(int i = 0; i < arg.nbThreads; i++)
		pthread_join(mt[i].tid, NULL);
	
	pthread_mutex_destroy(&mut);
	
	//Résultat
	for( int i = 0 ; i < arg.nbThreads; i++ )
		printf("Le résultat de l'addition est %d\n", *(mt[i].res));
		
	//Libération de la mémoire
	free(mt);
	free(tab);
}

void programmePrincipalBar (const arg_t arg)
{
	//Déclaration des variables 
	pthread_barrier_t bar;	

	message_t *mt;
	
	int *tab;
	int res = 0;
	int dec = arg.tailleTableau/arg.nbThreads;
	
	//Allocation de la mémoire
	tab 	= genereTableau (arg.tailleTableau);
	mt 		= malloc(arg.nbThreads * sizeof(message_t));
	
	pthread_barrier_init(&bar, NULL, arg.nbThreads);
	
	//Création des threads
	for(int i = 0; i < arg.nbThreads; i++)
	{
		mt[i].start = i*dec;
		mt[i].end   = i*dec + dec;
		mt[i].tab	= tab;
		mt[i].bar	= &bar;
		mt[i].res	= &res;
	}
	
	//Thread pour barriere
	for(int i = 0; i < arg.nbThreads; i++)
		pthread_create(&mt[i].tid, NULL, sommeTableauBar, &mt[i]);
	
	for(int i = 0; i < arg.nbThreads; i++)
		pthread_join(mt[i].tid, NULL);
	
	pthread_barrier_destroy(&bar);
	
	//Résultat
	for( int i = 0 ; i < arg.nbThreads; i++ )
		printf("Le résultat de l'addition est %d\n", *(mt[i].res));
		
	//Libération de la mémoire
	free(mt);
	free(tab);
}

void programmePrincipal (const arg_t arg)
{
	//Déclaration des variables
	pthread_mutex_t   mut;
	pthread_barrier_t bar;
	
	message_t *mt;
	
	int *tab;
	int res = 0;
	int dec = arg.tailleTableau/arg.nbThreads;
	
	//Allocation de la mémoire
	tab 	= genereTableau (arg.tailleTableau);
	mt 		= malloc(arg.nbThreads * sizeof(message_t));
	
	pthread_mutex_init(&mut, NULL);
	pthread_barrier_init(&bar, NULL, arg.nbThreads);
	
	//Création des threads
	for(int i = 0; i < arg.nbThreads; i++)
	{
		mt[i].start = i*dec;
		mt[i].end   = i*dec + dec;
		mt[i].tab	= tab;
		mt[i].mut	= &mut;
		mt[i].bar	= &bar;
		mt[i].res	= &res;
	}
	
	//Thread
	for(int i = 0; i < arg.nbThreads; i++)
		pthread_create(&mt[i].tid, NULL, sommeTableauMut, &mt[i]);
	
	for(int i = 0; i < arg.nbThreads; i++)
		pthread_join(mt[i].tid, NULL);
	
	pthread_mutex_destroy(&mut);
	pthread_barrier_destroy(&bar);
	
	//Résultat
	for( int i = 0 ; i < arg.nbThreads; i++ )
		printf("Le résultat de l'addition est %d\n", *(mt[i].res));
		
	//Libération de la mémoire
	free(mt);
	free(tab);
}

int main (int argc, char ** argv)
{
	arg_t a;

	srand(time(NULL));

	a = analyseArguments(argc, argv);
	programmePrincipalMut(a);
	printf("\n");
	programmePrincipalBar(a);
	printf("\n");
	programmePrincipal(a);
	
	return 0;
}
