#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACTION_SIZE 16
#define WORD_SIZE   48

/**
 * Defines a lexicon.
 */
struct liste
{
	char *mot;
	struct liste *suiv;
};
 
struct lexc 
{
	const char *nameLex;
	int iNbrMot;
	int isMutable;
	struct liste *prem;
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
	struct lexc *L = malloc(sizeof(struct lexc));
	struct liste *listeMot = malloc(sizeof(struct liste));
	
	if (L == NULL || listeMot == NULL)
		exit(EXIT_FAILURE);
	
	L -> prem = NULL;
	L -> iNbrMot = 0;
	L -> nameLex = name;
	L -> isMutable = mutable;
	
    return(L);
}

/**
 * Releases a lexicon data structure.
 *
 * @param      lexc             Lexicon to release.
 */
void lexc_fini(struct lexc *lexc)
{
	struct liste *Liste, *suiv;
	
	if(lexc -> prem != NULL)
	{
		Liste = lexc -> prem;
		while(Liste != NULL)
		{
			suiv = Liste -> suiv;
			free(Liste -> mot);
			free(Liste);
			Liste = suiv;
		}
	}

	
}

int lexc_add(struct lexc *lexc, const char *word)
{
	struct lexc *L;
	struct liste *Liste;
	
	Liste -> mot = word;
	L -> iNbrMot++;
	
    return 1;
}

int lexc_remove(struct lexc *lexc, const char *word)
{
	struct liste *tmp, *previous;
	
	if(Liste != NULL)
		return 0;
		
	
    return 1;
}

int lexc_check(struct lexc *lexc, const char *word)
{
    return 1;
}

int cmd_interpret(struct lexc *lexc, const char *cmd)
{
    return 0;
}
