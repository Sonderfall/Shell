#ifndef VAR_SUB_H
# define VAR_SUB_H

# define _BSD_SOURCE

typedef struct local_var s_local_var;

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include "my_int.h"
# include "../lexer/list_token.h"
# include "../main/main.h"

struct local_var
{
  char        *name;
  char        *var;
  s_local_var *next;
};


/**
** @brief Add or modify (name, var) in the static global list
** @param name The name to add
** @param var the variable to add
*/
void add_var(char *name, char *var);


/**
** @brief Get the variable associated with command
** @param cmd the command to substitute : $expr or ${expr}
** @return The value of the variable, which must be free
**         or NULL, if it does not exist
*/
char *parse_variable(char *cmd);


/**
** @brief Initialize the variables of the shell, $$ for example
*/
void init_var(void);


/**
** @brief Remove and free the node with the name = name
** @param name the name of the node
*/
void remove_var(char *name);


/**
** @brief Remove and free all the variables
*/
void remove_all_var(void);

#endif /* !VAR_SUB_H */
