#ifndef RULE_H
# define RULE_H

# include "ast_struct.h"

/* Note: this doesn't include the case rule */

/**
** @brief create a node for the rule while
** @param condition condition of the loop while
** @param group commands to execute in the loop while
** @return the node of the rule while
*/
s_rule_while *create_rule_while(s_and_or *condition, s_list *group);

/**
** @brief create a node for the rule if
** @param condition condition of the statement if
** @param action action in case of success
** @param elseif action in case of non success
** @return the node of the rule if
** @note elseif can be set to NULL
*/
s_rule_if *create_rule_if(s_and_or *condition, s_list *action, s_list *elseif);

/**
** @brief create a node for the rule for
** @param name name of the variable
** @param in condition of the loop for
** @param argc number of elements in the condition
** @param group command to execute
** @return the node of the rule for
*/
s_rule_for *create_rule_for(char *name, char **in, size_t argc, s_list *group);

/**
** @brief create a node for the rule until
** @param group group of commands to execute in the loop
** @param condition condition of the loop until
** @return the node of the rule until
*/
s_rule_until *create_rule_until(s_list *group, s_and_or *condition);

#endif /* !RULE_H */
