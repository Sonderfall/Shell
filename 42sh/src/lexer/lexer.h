#ifndef LEXER_H
# define LEXER_H

# include "list_token.h"
# include "group_lexer.h"
# include "quoting.h"
# include "dollar.h"
# include "getlineps2.h"
# include <string.h>
# include <stdio.h>


/**
** @brief Lexer take cmd, and separate into tokens
** @param cmd the command to lex
** @return the pointer to the list of tokens
*/
s_tokens *lexer(char *cmd);

#endif /* !LEXER_H */
