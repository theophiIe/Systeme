#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRINT_AND_RETURN(a)         { fprintf(stderr, "%s\n", a); return; }
#define PRINT_AND_RETURN_ELT(a, b)  { fprintf(stderr, "%s\n", a); return b; }

#define USAGE_STRING    "usage: action [word]\n" \
                        "  action: between {add, remove, check}\n" \
                        "  word: word targeted by the action\n"

#define ACTION_SIZE 16
#define WORD_SIZE   48

/**
 * Enumerates the possible actions.
 */
enum act_lexc {
    ACT_ADD,                    /**< 'add' action. */
    ACT_REMOVE,                 /**< 'remove' action. */
    ACT_CHECK,                  /**< 'check' action. */
    ACT_LIST,                   /**< 'list' action. */
    ACT_QUIT,                   /**< 'quit' action. */
    ACT_LAST
};

const char *act_str[ACT_LAST] = {"add", "remove", "check", "list", "quit"};

/**
 * Defines a lexicon entry.
 */
struct entry {
    char *word;                 /**< Entry name, consists in a word. */
    struct entry *next;         /**< Next entry, acts as a chained list. */
};

/**
 * Defines a lexicon.
 */
struct lexc {
    char *name;                 /**< Lexicon name. */
    int nb_words;               /**< Number of words in the lexicon. */
    struct entry *words;        /**< Words chained list. */
    int mutable;                /**< TRUE if the lexicon is mutable. */
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
    struct lexc *lexc;

    lexc = malloc(sizeof (*lexc));
    if (!lexc)
        PRINT_AND_RETURN_ELT("ERR: lexc allocation failed", NULL);

    lexc->name = strdup(name);
    if (!lexc->name) {
        free(lexc);
        PRINT_AND_RETURN_ELT("ERR: lexc name allocation failed", NULL);
    }

    lexc->mutable = mutable;
    lexc->nb_words = 0;
    lexc->words = NULL;

    return lexc;
}

/**
 * Releases a lexicon data structure.
 *
 * @param      lexc             Lexicon to release.
 */
void lexc_fini(struct lexc *lexc)
{
    struct entry *next;
    struct entry *ptr;

    if (!lexc)
        return;

    ptr = lexc->words;
    while (ptr) {
        next = ptr->next;
        free(ptr->word);
        free(ptr);
        ptr = next;
    }

    free(lexc->name);
    free(lexc);
}

/**
 * Checks that a word exists in a lexicon.
 *
 * @param      lexc             Lexicon to search in.
 * @param[in]  word             Word to search.
 *
 * @return     0 if the word was found, 1 else.
 */
static int _lexc_check(struct lexc *lexc, const char *word)
{
    struct entry *ptr;

    ptr = lexc->words;
    while (ptr) {
        if (! strcmp(ptr->word, word))
            return 0;
        ptr = ptr->next;
    }

    return 1;
}

/**
 * Adds a word in a lexicon.
 * 
 * Will fail if the word already exists in the lexicon.
 *
 * @param      lexc             Lexicon to add to.
 * @param[in]  word             Word to add.
 *
 * @return     0 if the word was added, 1 else.
 */
int lexc_add(struct lexc *lexc, const char *word)
{
    struct entry *new;
    struct entry *ptr;

    if (!lexc)
        PRINT_AND_RETURN_ELT("ERR: lexicon is not allocated", 1);

    if (!lexc->mutable)
        PRINT_AND_RETURN_ELT("ERR: lexicon is not mutable", 1);

    if (!word)
        PRINT_AND_RETURN_ELT("ERR: word is not allocated", 1);

    if (!_lexc_check(lexc, word))
        PRINT_AND_RETURN_ELT("ERR: entry already exists in the lexicon", 1);

    new = malloc(sizeof (*new));
    if (!new)
        PRINT_AND_RETURN_ELT("ERR: entry allocation failed", 1);

    new->next = NULL;
    new->word = strdup(word);
    if (!new->word) {
        free(new);
        PRINT_AND_RETURN_ELT("ERR: entry name allocation failed", 1);
    }

    if (lexc->nb_words++ == 0) {
        lexc->words = new;
        return 0;
    }

    ptr = lexc->words;
    while (ptr->next)
        ptr = ptr->next;

    ptr->next = new;

    return 0;  
}

/**
 * Removes a word in a lexicon.
 * 
 * Will fail if the word does not exist in the lexicon.
 *
 * @param      lexc             Lexicon to remove from.
 * @param[in]  word             Word to remove.
 *
 * @return     0 if the word was removed, 1 else.
 */
int lexc_remove(struct lexc *lexc, const char *word)
{
    struct entry *prv = NULL;
    struct entry *ptr;

    if (!lexc)
        PRINT_AND_RETURN_ELT("ERR: lexicon is not allocated", 1);

    if (!lexc->mutable)
        PRINT_AND_RETURN_ELT("ERR: lexicon is not mutable", 1);

    if (!word)
        PRINT_AND_RETURN_ELT("ERR: word is not allocated", 1);

    ptr = lexc->words;

    while (ptr && strcmp(ptr->word, word)) {
        prv = ptr;
        ptr = ptr->next;
    }

    if (ptr == NULL)
        PRINT_AND_RETURN_ELT("ERR: entry did not exist", 1);

    --lexc->nb_words;

    if (!prv)
        lexc->words = ptr->next;
    else
        prv->next = ptr->next;

    free(ptr->word);
    free(ptr);
    return 0;
}

/**
 * Prints to stdout the result of a word check in a lexicon.
 *
 * @param      lexc             Lexicon to search in.
 * @param[in]  word             Word to search.
 *
 * @return     0 if the word was found, 1 else.
 */
int lexc_check(struct lexc *lexc, const char *word)
{
    int rc;

    if (!lexc)
        PRINT_AND_RETURN_ELT("ERR: lexicon is not allocated", 1);

    if (!word)
        PRINT_AND_RETURN_ELT("ERR: word is not allocated", 1);

    rc = _lexc_check(lexc, word);

    if (!rc)
        printf("%s is in the lexicon\n", word);
    else
        printf("%s is not in the lexicon\n", word);

    return rc;
}

/**
 * Lists the words of a lexicon.
 *
 * @param      lexc             Lexicon to browse.
 * @param      none             Unused.
 * 
 * @return     0 if the list was done, 1 if the lexc is NULL.
 */
int lexc_list(struct lexc *lexc, const char *none)
{
    struct entry *ptr;

    if (!lexc)
        PRINT_AND_RETURN_ELT("ERR: lexicon does not exist", 1);

    ptr = lexc->words;

    printf("%d words:", lexc->nb_words);
    while (ptr) {
        printf(" %s", ptr->word);
        ptr = ptr->next;
    }
    printf("\n");

    return 0;
}

int (*act_func[ACT_LAST])(struct lexc *, const char *) =
    {lexc_add, lexc_remove, lexc_check, lexc_list, NULL};

/**
 * Interprets and executes a command on a lexicon.
 *
 * @param      lexc             Lexicon to use.
 * @param[in]  cmd              Commant to interpret.
 *
 * @return     0 if the 'quit' command was entered, 1 else.
 */
int cmd_interpret(struct lexc *lexc, const char *cmd)
{
    char action[ACTION_SIZE];
    char word[WORD_SIZE];
    enum act_lexc act;
    int n_args;

// parses cmd to retrieve action and word
    n_args = sscanf(cmd, "%s %s", action, word);

    for (act = 0; act < ACT_LAST && strcmp(action, act_str[act]); ++act);

// executes the given action
    switch (act) {
    case ACT_ADD:
    case ACT_REMOVE:
    case ACT_CHECK:
        if (n_args != 2)
            PRINT_AND_RETURN_ELT("ERR: bad usage\n" USAGE_STRING, 1);

    case ACT_LIST:
        if (act == ACT_LIST && n_args != 1)
            PRINT_AND_RETURN_ELT("ERR: bad usage\n" USAGE_STRING, 1);

        act_func[act](lexc, word);
        return 1;

    case ACT_QUIT:
        return 0;

    default:
        PRINT_AND_RETURN_ELT("ERR: bad usage\n" USAGE_STRING, 1);
    }

}