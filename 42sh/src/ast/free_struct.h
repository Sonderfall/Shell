#ifndef FREE_STRUCT_H
# define FREE_STRUCT_H

# include "ast_struct.h"

/**
** @brief free the node funcdec and all his child
** @param funcdec top node to free
*/
void free_struct_funcdec(s_funcdec *funcdec);

/**
** @brief free the node and_or and all his child
** @param and_or top node to free
*/
void free_struct_and_or(s_and_or *and_or);

/**
** @brief free the node cmd and all his child
** @param cmd top node to free
*/
void free_struct_cmd(s_cmd *cmd);

/**
** @brief free the node redirection and all his child
** @param redirect top node to free
*/
void free_struct_redirection(s_redirection *redirect);

#endif /* !FREE_STRUCT_H */
