#ifndef PROMPT_H
# define PROMPT_H

# include <stdlib.h>
# include <libgen.h>
# include <string.h>
# include <stdio.h>

/**
** @brief return the value of the parse PS1
** @param ps select ps1 or ps2
*/
char *set_prompt(const char *ps);

#endif /* !PROMPT_H */
