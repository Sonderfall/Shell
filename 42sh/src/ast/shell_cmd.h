#ifndef SHELL_CMD_H
# define SHELL_CMD_H

# include "ast_struct.h"

/**
** @brief create a shell command node
** @param cmd command value for the node
** @param type type of command
*/
s_shell_cmd *create_struct_shell_cmd(u_shell_command    cmd,
                                     e_type_shell_cmd   type);

/**
** @brief free a shell command
** @param cmd node of the shell command
*/
void free_struct_shell_cmd(s_shell_cmd *cmd);

#endif /* !SHELL_CMD_H */
