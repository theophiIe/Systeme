#ifndef LEXC_ERR_H
#define LEXC_ERR_H

//Error label & error code
#define EXEC_SUCCESS            0
#define ERR_WORD_SIZE_TOO_LARGE 1
#define ERR_WORD_EXISTS         2
#define ERR_LEXC_LOCK_ON        3
#define ERR_NULL_PARAMETER      4
#define ERR_WORD_NOT_FOUND      5
#define ERR_LIST_EMPTY          6
#define ERR_UNKNOWN_COMMAND     7
#define ERR_BAD_LOCK_VALUE      8

//
static char err_msg[9][100] = {
			      "",
			      "word size is too large",
			      "word already exists",
			      "lexicon lock is ON",
			      "NULL parameter given",
			      "word not found",
			      "lexicon is empty",
			      "uknown command",
			      "bad lock value"
};

//
void lexc_error(int err_code);
  
#endif
