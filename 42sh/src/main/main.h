#ifndef SH_H
# define SH_H

# define _SVID_SOURCE
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "parser_options.h"
# include "../execution/execution.h"
# include "../substitution/var_sub.h"
# include "../substitution/alias.h"
# include "../ast/ast.h"
# include "../ast_printer/ast_printer.h"
# include "../lexer/lexer.h"
# include "../parser/parser.h"
# include "../prompt/prompt.h"
# include "../readline/readline.h"
# include "../substitution/var_sub.h"
# include "../substitution/my_int.h"

typedef struct basename
{
  int       ast_print;
  char      *name;
  s_tokens  *token;
  s_list    *list;
} s_basename;

typedef struct global s_global;
struct global
{
  s_aliases      *aliases;
  s_local_var    *local_vars;
  struct termios original_term;
  int            prev_fd;
  int            cur_fd;
  pid_t          cur_pid;
};

s_global g_global;

/**
** @brief print the error on the current command
** @param cmd current command
*/
void print_error_cmd(char *cmd);

/**
** @brief main function of the shell continue to run after each command
** @return the result of the last command
*/
int loop_prompt(void);

/**
** @brief same as loop_prompt but also print the AST of the last command
** @return the result of the last command
** @see loop_prompt(void)
*/
int loop_prompt_ast(void);

/**
** @brief run only one group of commands then exit
** @param cmd command to run
** @return the return value of the command
*/
int run_once(char *cmd);

/**
** @brief verify each arguments parse and launch appropriate functions
** @param argc number of argument
** @param argv vector of argument
** @return return the result of the appropriate function
*/
int check_args(int argc, char **argv);

#endif /* !SH_H */
