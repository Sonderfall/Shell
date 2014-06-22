#ifndef STRUCT_CREATE_H
# define STRUCT_CREATE_H

# include "ast_struct.h"

/**
** @brief create a node and_or
** @param pipeline pipeline of the and or node
** @param type type of link with the next and or node
** @return node and_or created
*/
s_and_or *create_and_or(s_pipeline *pipeline, e_and_or_type type);

/**
** @brief create a node cmd
** @param command command for the node
** @param type type of the command
** @return node s_cmd created
*/
s_cmd *create_cmd(u_command command, e_command_type type);

/**
** @brief create a node redirection
** @param word word to add on the node redirection
** @param type type of redirection
** @param ionumber id of the io we want to redirect to
** @return node redirection created
*/
s_redirection *create_redirection(char *word, e_redirect type, int ionumber);

/**
** @brief create a node funcdec
** @param name name of the function
** @param cmd shell command which correspond to the function
** @return the node of the function
*/
s_funcdec *create_funcdec(char *name, s_shell_cmd *cmd);

#endif /* !STRUCT_CREATE_H */
