#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACTION_SIZE 16
#define WORD_SIZE   48

/**
 * Defines a lexicon.
 */

struct lexc 
{
	const char *mot;
	int *nbreMot;
	const char *nomLexique;
	int modif;
	struct lexc *prec;
};

/**
 * Initializes a lexicon data structure.
 * 
 * The lexicon must be freed using the lexc_fini() function.
 *
 * @param[in]  name             Lexicon name.
 * @param[in]  mutable          TRUE if the lexicon is mutable.
 *
 * @return     New lexicon.
 */
struct lexc *lexc_init(const char *name, const int mutable)
{
	struct lexc *lexique = malloc(sizeof(struct lexc));
	
	if(lexique == NULL)
		exit(EXIT_FAILURE);
	
	lexique -> mot = NULL;
	lexique -> nbreMot = 0;
	lexique -> nomLexique = name;
	lexique -> modif = mutable;
	
    return lexique;
}

/**
 * Releases a lexicon data structure.
 *
 * @param      lexc             Lexicon to release.
 */
void lexc_fini(struct lexc *lexc)
{
	struct lexc *tmp;
	while (lexc)
	{
		tmp = (lexc)->prec;
		free(lexc);
		lexc = tmp;
	}
}

int lexc_add(struct lexc *lexc, const char *word)
{
	struct lexc *lexique;
	
	if(!lexique)
		return 1;
	
	lexique -> mot = word;
	lexique -> prec = lexc;
	lexc = lexique;
	lexique ->nbreMot++;
	
    return 0;
}

int lexc_remove(struct lexc *lexc, const char *word)
{
	/*
	    int Val;
        pile *tmp;
        if(!*p) return -1;     /* Retourne -1 si la pile est vide. 
        
        tmp = (*p)->prec;
        Val = (*p)->valeur;
        free(*p);
        *p = tmp;       /* Le pointeur pointe sur le dernier élément. 
        return Val;     /* Retourne la valeur soutirée de la pile. 
	 
	 */
	
	struct lexc *tmp;
	if(!lexc)
		return 1;
	
	while(lexc)
	{
		lexc = lexc->prec;
		if(lexc->mot == word)
		{
			tmp = lexc->prec;
			free(lexc);
			lexc = tmp;
			lexc->nbreMot--;
		}
	}
	
    return 0;
}

int lexc_check(struct lexc *lexc, const char *word)
{
    return 1;
}

int cmd_interpret(struct lexc *lexc, const char *cmd)
{
    return 0;
}
