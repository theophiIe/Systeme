#ifndef __H_LEXC__
#define __H_LEXC__

/**
 * Defines a lexicon.
 */
struct lexc;

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
struct lexc *lexc_init(const char *name, const int mutable);

/**
 * Releases a lexicon data structure.
 *
 * @param      lexc             Lexicon to release.
 */
void lexc_fini(struct lexc *lexc);

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
int lexc_add(struct lexc *lexc, const char *word);

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
int lexc_remove(struct lexc *lexc, const char *word);

/**
 * Prints to stdout the result of a word check in a lexicon.
 *
 * @param      lexc             Lexicon to search in.
 * @param[in]  word             Word to search.
 *
 * @return     0 if the word was found, 1 else.
 */
int lexc_check(struct lexc *lexc, const char *word);

/**
 * Lists the words of a lexicon.
 *
 * @param      lexc             Lexicon to browse.
 * @param      none             Unused.
 * 
 * @return     0 if the list was done, 1 if the lexc is NULL.
 */
int lexc_list(struct lexc *lexc, const char *none);

/**
 * Retrieves and executes a command on a lexicon.
 *
 * @param      lexc             Lexicon to use.
 * @param[in]  cmd              Command to interpret.
 *
 * @return     0 if the 'quit' command was entered, 1 else.
 */
int cmd_interpret(struct lexc *lexc, const char *cmd);

#endif