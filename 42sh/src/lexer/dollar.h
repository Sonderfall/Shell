#ifndef DOLLAR_H
# define DOLLAR_H

# include <stdlib.h>
# include <string.h>
# include "list_token.h"
# include "getlineps2.h"

s_tokens *lexDollar(char *cmd, int *index, s_tokens *token_list);

#endif /* !DOLLAR_H */
