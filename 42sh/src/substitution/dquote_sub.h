#ifndef DQUOTE_SUB_H
# define DQUOTE_SUB_H

# include <stdlib.h>
# include "var_sub.h"
# include "../lexer/getlineps2.h"

/**
** @brief Parse Tok_d_quote tokens, and subsititude $.. and \
** @param dquote_str The tok_d_quote token
** @return the subsituted string
*/
char *sub_double_quote(char *dquote_str);

#endif /* !DQUOTE_SUB_H */
