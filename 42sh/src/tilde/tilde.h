#ifndef TILDE_H
# define TILDE_H

# include "../variable/variable.h"

/**
** @brief parse the tilde value and return the appropriate value
** @param tilde the specify tilde send by the user
** @param list variable struct
** @return string containing the corresponding value
*/
char *parse_tilde(char *tilde);

#endif /* !TILDE_H */
