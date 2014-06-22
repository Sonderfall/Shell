#ifndef QUOTING_H
# define QUOTING_H

# include "list_token.h"
# include "getlineps2.h"

char *lex_quoting(char *cmd, int *index_cmd, char *token, int *index_tok);
int  is_quote_c(char c);

#endif /* !QUOTING_H */
