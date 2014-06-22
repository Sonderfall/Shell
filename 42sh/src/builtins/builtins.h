#ifndef BUILTINS_H
# define BUILTINS_H
# define _BSD_SOURCE
# define _XOPEN_SOURCE
# define _GNU_SOURCE
# define _SVID_SOURCE

# include "../parser/parser.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

/**
** @brief check if the token matches if a builtin command
** @param cmd cmd from the input command
** @return an int, 0 if the token is a builtin, 1 otherwise
*/
int is_builtins(s_simple_cmd *cmd);

/**
** @brief second part of the previous function
*/
int is_builtins_next(int res, s_simple_cmd *cmd);

/**
** @brief do the cd builtin
** @param cmd cmd from the input command
** @return an int, 0 if the token is a builtin, 1 otherwise
*/
int builtin_cd(s_simple_cmd *cmd);

/**
** @brief do the export builtin
** @param cmd cmd from the input command
** @return an int, 0 if the token is a builtin, 1 otherwise
*/
int builtin_export(s_simple_cmd *cmd);

/**
** @brief do the shopt builtin
** @param cmd cmd from the input command
** @return an int, 0 if the token is a builtin, 1 otherwise
*/
/*int builtin_shopt(s_simple_cmd *cmd);*/

/**
** @brief do the echo builtin
** @param cmd from the input command
** @return an int, 0 if the token is a builtin, 1 otherwise
*/
int builtin_echo(s_simple_cmd *cmd);

/**
** @brief do the break builtin
** @param cmd cmd from the input command
** @return an int, 0 if the token is a builtin, 1 otherwise
*/
/*int builtin_break(s_simple_cmd *cmd);*/

/**
** @brief do the history builtin
** @param cmd cmd from the input command
** @return an int, 0 if the token is a builtin, 1 otherwise
*/
/*int builtin_history(s_simple_cmd *cmd);*/

/**
** @brief do the continue builtin
** @param cmd cmd from the input command
** @return an int, 0 if the token is a builtin, 1 otherwise
*/
/*int builtin_continue(s_simple_cmd *cmd);*/

/**
** @brief do the alias builtin
** @param cmd cmd from the input command
** @return an int, 0 if the token is a builtin, 1 otherwise
*/
/*int builtin_alias(s_simple_cmd *cmd);*/

/**
** @brief do the unalias builtin
** @param cmd cmd from the input command
** @return an int, 0 if the token is a builtin, 1 otherwise
*/
/*int builtin_unalias(s_simple_cmd *cmd);*/

/**
** @brief do the source builtin
** @param cmd cmd from the input command
** @return an int, 0 if the token is a builtin, 1 otherwise
*/
int builtin_source(s_simple_cmd *cmd);

/**
** @brief do the source builtin
** @param cmd cmd from the input command
** @return an int, 0 if the token is a builtin, 1 otherwise
*/
int builtin_exit(s_simple_cmd *cmd);

enum opt
{
  NO_OPT,
  S_OPT,
  U_OPT,
  Q_OPT
};

typedef enum opt e_opt;

#endif /* !BUILTINS_H */
