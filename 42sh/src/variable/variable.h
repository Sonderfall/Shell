#ifndef VARIABLE_H
# define VARIABLE_H

typedef struct variable s_variable;
struct variable
{
  char              *name;
  char              *value;
  struct variable   *next;
  struct variable   *prev;
};

s_variable *g_variable;

/**
** @brief add a new variable to the list
** @param list list of variable already existing
** @param name name of the variable
** @param value value of the variable
*/
void add_variable(s_variable **list, char *name, char *value);

/**
** @brief remove a specifi variable of the list
** @param list list of variables
** @param name name of the variable
*/
void remove_variable(s_variable **list, char *name);

/**
** @brief remove all the varaible
** @param list list of variables
*/
void remove_all_variables(s_variable **list);

/**
** @brief return the value of a given variable
** @param list list of variable
** @param name name of the variable
** @note return NULL if the variable doesn't exist
*/
char *get_variable_value(s_variable *list, char *name);

#endif /* !VARIABLE_H */
