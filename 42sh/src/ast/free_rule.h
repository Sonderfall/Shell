#ifndef FREE_RULE_H
# define FREE_RULE_H

# include "ast_struct.h"

/**
** @brief free node rule for and all hist child
** @param rule_for top node to free
*/
void free_rule_for(s_rule_for *rule_for);

/**
** @brief free node rule while and all his child
** @param rule_while top node to free
*/
void free_rule_while(s_rule_while *rule_while);

/**
** @brief free node until and all his child
** @param rule_until top node to free
*/
void free_rule_until(s_rule_until *rule_until);

/**
** @brief free node if and all his child
** @param rule_if top node to free
*/
void free_rule_if(s_rule_if *rule_if);

#endif /* !FREE_RULE_H */
