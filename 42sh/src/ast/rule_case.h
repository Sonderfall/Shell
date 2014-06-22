#ifndef RULE_CASE_H
# define RULE_CASE_H

# include "ast_struct.h"

/**
** @brief add an item case to the structure
** @param rule_case structure case
** @param item item to add to the structure
** @param name name of the value to compare
** @note the name is only set when rule_case is NULL
*/
void add_rule_case(s_rule_case  *rule_case,
                   s_case_item  *item,
                   char         *name);

/**
** @brief create a node for the case item
** @param value value to compare for the case item
** @param group group of command to execute in case of success
** @return the node of the case item
*/
s_case_item *create_rule_case_item(char *value, s_list *group);

/**
** @brief free the structure rule case and his child
** @param rule_case top node to free
*/
void free_rule_case(s_rule_case *rule_case);

/**
** @brief free the node case item and his child
** @param case_item the top node to free
*/
void free_rule_case_item(s_case_item *case_item);

#endif /* !RULE_CASE_H */
