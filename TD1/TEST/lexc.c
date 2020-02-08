#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACTION_SIZE 16
#define WORD_SIZE   48

/**
 * Defines a lexicon.
 */
 
typedef struct Element Element;
struct Element
{
	char *mot;
	Element *suivant;
};

struct lexc 
{
	Element *premier;
	int nbreMot;
	int isMutable;
	const char *nameLex;
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
	struct lexc *liste = malloc(sizeof(struct lexc));
	Element *element = malloc(sizeof(Element));
	
	if(liste == NULL || element == NULL)
	{
			exit(EXIT_FAILURE);
	}
	
	element -> mot = NULL;
	element -> suivant = NULL;
	liste -> premier = element;
	liste -> isMutable = mutable;
	liste  -> nameLex = name;
	liste -> nbreMot = 0;
	
    return liste;
}

/**
 * Releases a lexicon data structure.
 *
 * @param      lexc             Lexicon to release.
 */
void lexc_fini(struct lexc *lexc)
{
	
	
	if(lexc -> premier != NULL)
	{
		
	}
	
	
	
}

int lexc_add(struct lexc *lexc, const char *word)
{
	Element *nouveau = malloc(sizeof(*nouveau));
	
	nouveau -> mot = word;
	nouveau -> suivant = lexc -> premier;
	lexc -> premier = nouveau;
	lexc -> nbreMot++;
	
    return 1;
}

int lexc_remove(struct lexc *lexc, const char *word)
{
	
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
