#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Enumération des différents opérateurs possibles
typedef enum 
{
	OCD_SOMME,
	OCD_MOYENNE,
	OCD_MAX,
	OCD_MIN,
	OCD_TOTAL
} opcode_t;

// Structure contenant les arguments du programme
typedef struct 
{
	int nbThreads;			//< Nombre de threads à utiliser
	int tailleTableau;		//< Taille du tableau utilisé pour la réduction
	opcode_t code;			//< Opération à réaliser
} arg_t;

// Structure contenant les informations nécessaires au thread
typedef struct 
{
	int *tab;		//< Tableau d'entiers à traiter
	int start;		//< Indice de début de traitement
	int end;		//< Indice de fin de traitement (non compris)
	int res;		//< Résultat local
} message_t;

// Alias de pointeurs de fonction
typedef int (* ptrVerif) (int *, int, int);

// Fonction thread -- calcule la somme locale d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * sommeTableau (void * arg)
{
	message_t *mt = (message_t *) arg;
	
	for(int i = mt -> start; i < mt -> end; i++)
		mt -> res += mt -> tab[i];
	
	pthread_exit(NULL);
	
	return NULL;
}

// Fin de la réduction -- calcule la somme globale
// \param	msg				Messages issus de l'exécution des threads,
//							contiennent les résultats locaux
// \param	nbThreads		Nombre de threads, et donc de messages
// \return					Résultat global
int reducSomme (message_t * msg, int nbThreads)
{
	int res = 0;
	
	for(int i = 0; i < nbThreads; i++)
		res += msg[i].res;
	
	return res;
}

// Fonction thread -- calcule la moyenne locale d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * moyenneTableau (void * arg)
{
	message_t *mt = (message_t *) arg;
	
	for(int i = mt->start; i < mt->end; i++)
		mt -> res += mt -> tab[i];
		
	mt -> res = mt -> res / (mt -> end - mt -> start);
	
	pthread_exit(NULL);	
	
		return NULL;
}

// Fin de la réduction -- calcule la moyenne globale
// \param	msg				Messages issus de l'exécution des threads,
//							contiennent les résultats locaux
// \param	nbThreads		Nombre de threads, et donc de messages
// \return					Résultat global
int reducMoyenne (message_t * msg, int nbThreads)
{
	int res = 0;
	
	for(int i = 0; i < nbThreads; i++)
		res += msg[i].res;
	
	res /= nbThreads;
	
	return res;
}

// Fonction thread -- calcule le maximum local d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * maxTableau (void * arg)
{
	message_t *mt = (message_t *) arg;
	
	mt -> res = -1;
	
	for(int i = mt->start; i < mt->end; i++)
	{
		if(mt -> res < mt -> tab[i])
			mt -> res = mt -> tab[i];
	}	
	
	pthread_exit(NULL);	
	
	return NULL;
}

// Fin de la réduction -- calcule le maximum global
// \param	msg				Messages issus de l'exécution des threads,
//							contiennent les résultats locaux
// \param	nbThreads		Nombre de threads, et donc de messages
// \return					Résultat global
int reducMax (message_t * msg, int nbThreads)
{
	int res = -1;
	
	for(int i = 0; i < nbThreads; i++)
	{
		if(res < msg[i].res)
			res = msg[i].res;
	}
	
	return res;
}

// Fonction thread -- calcule le minimum local d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * minTableau (void * arg)
{
	message_t *mt = (message_t *) arg;
	
	mt -> res = 101;
	
	for(int i = mt->start; i < mt->end; i++)
	{
		if(mt -> res > mt -> tab[i])
			mt -> res = mt -> tab[i];
	}	
	
	pthread_exit(NULL);
	
	return NULL;	
}

// Fin de la réduction -- calcule le minimum global
// \param	msg				Messages issus de l'exécution des threads,
//							contiennent les résultats locaux
// \param	nbThreads		Nombre de threads, et donc de messages
// \return					Résultat global
int reducMin (message_t * msg, int nbThreads)
{
	int res = 101;
	
	for(int i = 0; i < nbThreads; i++)
	{
		if(res > msg[i].res)
			res = msg[i].res;
	}
	
	return res;
}

// NE PAS TOUCHER
// Fonction de vérification -- somme des éléments du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifSomme (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 0;

	for (i = 0; i < tailleTableau; ++i)
		tmp += tableau [i];

	return resultat == tmp;
}

// NE PAS TOUCHER
// Fonction de vérification -- moyenne des éléments du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifMoyenne (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 0;

	if (tailleTableau == 0)
		return resultat == 0;

	for (i = 0; i < tailleTableau; ++i)
		tmp += tableau [i];

	return resultat == (tmp / tailleTableau);
}

// NE PAS TOUCHER
// Fonction de vérification -- maximum du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifMax (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 0;

	for (i = 0; i < tailleTableau; ++i)
		tmp = (tmp < tableau [i] ? tableau [i] : tmp);

	return resultat == tmp;
}

// NE PAS TOUCHER
// Fonction de vérification -- minimum du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifMin (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 101;

	for (i = 0; i < tailleTableau; ++i)
		tmp = (tmp > tableau [i] ? tableau [i] : tmp);

	return resultat == tmp;
}

// Analyse des arguments du programme. Quitte si le nombre d'arguments est
// différent de 4. Remplit la structure de données des arguments.
// \param	argc			Nombre d'arguments
// \param	argv			Arguments
// \return					Structure de données des arguments
arg_t analyseArguments (int argc, char ** argv)
{
	if(argc < 4)
	{
		printf("Erreur, nombre d'argument non valide\n");
		exit(EXIT_FAILURE);
	}
	
	arg_t at;
	
	at.nbThreads 	 = atoi(argv[1]);
	printf("Le nombre de thread est de : %d\n", at.nbThreads);
	
	at.tailleTableau = atoi(argv[2]);
	printf("Le taille du tableau est de : %d\n", at.tailleTableau);
	
	switch (*argv[3])
	{
		case '+':
			at.code = OCD_SOMME;
			printf("On a : %c qui correspond au num : %d\n", *argv[3], at.code);
			break;
		
		case '/':
			at.code = OCD_MOYENNE;
			printf("On a : %c qui correspond au num : %d\n", *argv[3], at.code);
			break;
		
		case 'M':
			at.code = OCD_MAX;
			printf("On a : %c qui correspond au num : %d\n", *argv[3], at.code);
			break;
		
		case 'm':
			at.code = OCD_MIN;
			printf("On a : %c qui correspond au num : %d\n", *argv[3], at.code);
			break;
		
		default:
			printf("L'argument : %c n'est pas reconnue", *argv[3]);
			exit(EXIT_FAILURE);
	}
		
	return at;
}

// NE PAS TOUCHER
// Récupération de la fonction de vérification à partir de l'opcode
// \param	opcode 			Code de l'opération
// \return					Pointeur de la fonction de vérification
ptrVerif decodeOpcodeVerif (const opcode_t o) {
	switch (o) {
		case OCD_SOMME:		return verifSomme;
		case OCD_MOYENNE:	return verifMoyenne;
		case OCD_MAX:		return verifMax;
		case OCD_MIN:		return verifMin;
		default:
			printf ("L'opération n'a pas été reconnue\n");
			exit (-1);
	}
}

// Génération du tableau avec des entiers compris entre 1 et 100.
// \param	tailleTableau	Taille du tableau d'entiers
// \return					Tableau d'entiers
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

// Fonction chargée de la réduction multi-threadé, elle va initialiser les
// différentes variables utilisées par les threads (tableau d'entier, messages,
// etc.) puis créer les threads. Une fois l'exécution des threads terminée et
// la réduction opérée, la vérification du résultat est faite.
// \param	arg 			Arguments du programme décodés
void programmePrincipal (const arg_t arg)
{
	// Déclaration des variables
	pthread_t *tab_tid;
	message_t *mt;
	
	void *start_routine;
	
	int * tab; 
	int res;
	int dec;
	
	// Allocation de la mémoire
	tab = genereTableau (arg.tailleTableau);
	
	mt 		= malloc(arg.nbThreads * sizeof(message_t));
	tab_tid	= malloc(arg.nbThreads * sizeof(pthread_t));
	
	// Initialisation des variables et création des threads
	
	
	switch (arg.code)
	{
		case 0 :
			start_routine = sommeTableau;
			break;
			
		case 1 :
			start_routine = moyenneTableau;
			break;
			
		case 2 :
			start_routine = maxTableau;
			break;
			
		case 3 :
			start_routine = minTableau;
			break;			
		
		default:
			printf("Erreur arg.code \n");
			exit(EXIT_FAILURE);
	}
	
	dec = arg.tailleTableau/arg.nbThreads;
	
	for(int i = 0; i < arg.nbThreads; i++)
	{
		mt[i].start = i*dec;
		mt[i].end   = i*dec + dec;
		mt[i].res   = 0;
		mt[i].tab = tab;
	
	}
	
	for(int i = 0; i < arg.nbThreads; i++)
		pthread_create(&tab_tid[i], NULL, start_routine, &mt[i]);
		
	// Jointure
	for(int i = 0; i < arg.nbThreads; i++)
		pthread_join(tab_tid[i], NULL);
		
	// Réduction et affichage du résultat
	switch (arg.code)
	{
		case 0 :
			res = reducSomme(mt, arg.nbThreads);
			break;
			
		case 1 :
			res = reducMoyenne(mt, arg.nbThreads);
			break;
			
		case 2 :
			res = reducMax(mt, arg.nbThreads);
			break;
			
		case 3 :
			res = reducMin(mt, arg.nbThreads);
			break;
			
		default:
			printf("Erreur arg.code \n");
			exit(EXIT_FAILURE);
	}
	
	// NE PAS TOUCHER
	if ( (* (decodeOpcodeVerif (arg.code) ) ) (tab, arg.tailleTableau, res) )
		printf ("Le resultat est juste.\n");
		
	else printf ("Le resultat est faux.\n");
	
	// FIN
	printf("le resultat est : %d\n", res);
	
	// Libération de la mémoire
	free(tab_tid);
	free(tab);
	free(mt);
}

// NE PAS TOUCHER
// Fonction main -- analyse les arguments donnés au
// programme, puis exécute le programme principal, chargé de la réduction
// multi-threadée.
// \param	argc			Nombre d'arguments
// \param	argv			Arguments
// \return					Code de retour du programme (0 en cas de réussite)
int main (int argc, char ** argv)
{
	arg_t a;

	srand (time (NULL) );

	a = analyseArguments (argc, argv);
	programmePrincipal (a);
	
	return 0;
}
