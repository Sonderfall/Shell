#ifndef ALIAS_H
# define ALIAS_H

# include <stdlib.h>
# include <string.h>

typedef struct aliases s_aliases;
struct aliases
{
  char      *name;
  char      *value;
  s_aliases *next;
};


/**
** @brief Add or Update (if already exists) an alias in the alias's list
** @param name name of the alias
** @param value value of the alias
*/
void add_alias(char *name, char *value);

/**
** @brief Remove an alias from the list
** @param name the name of the alias to remove
*/
void unalias(char *name);

/**
** @brief Destroy and free all the allocated aliases
*/
void destroy_aliases(void);


/**
** @brief Get the alias associated with name. Prevents also infinite loop
** @param name name of the alias
** @return return the alias associated with name
*/
char *get_alias(char *name);

#endif /* !ALIAS_H */
