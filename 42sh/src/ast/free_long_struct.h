#ifndef FREE_LONG_STRUCT_H
# define FREE_LONG_STRUCT_H

# include "ast_struct.h"

/**
** @brief free the node list and all his child
** @param list top node to free
*/
void free_struct_list(s_list *list);

/**
** @brief free the node pipeline and all his child
** @param pipeline top node to free
*/
void free_struct_pipeline(s_pipeline *pipeline);

/**
** @brief free the node simple command and all his child
** @param cmd node to free
*/
void free_struct_simple_cmd(s_simple_cmd *cmd);

#endif /* !FREE_LONG_STRUCT_H */
