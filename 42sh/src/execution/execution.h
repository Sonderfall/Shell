#ifndef EXECUTION_H
# define EXECUTION_H

# define _SVID_SOURCE
# include "../ast/ast.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../main/main.h"
# include "../substitution/var_sub.h"
# include "../tilde/tilde.h"

# define BAD_REDIRECTION (void *) -1

/**
** @brief call all the and_or instruction in list
** @param list structure containing the and_or instruction
** @return the return value of the and_or execution
*/
int execute_list(s_list *list);

/**
** @brief call pipeline, and another time and_or if there is AND or OR
** @param and_or structure containing the pipeline and and_or instruction
** @return
*/
int execute_and_or(s_and_or *and_or);

/**
** @brief handle the pipe behavior
** @param pipeline structure containing the pipeline instruction
** @return
*/
int execute_pipeline(s_pipeline *pipeline);

/**
** @brief execute a simple cmd
** @param cmd structure containing the simple cmd instruction
** @return
*/
int execute_simple_commands(s_simple_cmd *cmd);

/**
** @brief call the appropriate execution function, depend on cmd->type
** @param cmd structure containing the shell_cmd instruction
** @return
*/
int execute_shell_command(s_shell_cmd *cmd);

/**
** @brief
** @param cmd structure containing the funcdec instruction
** @return
*/
int execute_funcdec(s_funcdec *cmd);

/**
** @brief execute a simple cmd
** @param cmd structure containing the simple cmd instruction
** @return
*/
int execute_simple_cmd(s_simple_cmd *cmd);

/**
** @brief call the appripriate execution function depend on cmd->type
** @param cmd structure, containing an command to execute
** @return
*/
int execute_cmd(s_cmd *cmd);

/**
** @brief handle the if behevior
** @param rule containing condition, action, and elseif
** @return
*/
int execute_rule_if(s_rule_if *rule);

/**
** @brief handle the for behavior
** @param rule containing the condition, and instructions
** @return
*/
int execute_rule_for(s_rule_for *rule);

/**
** @brief handle the until behavior
** @param rule containing the condition, and instructions
** @return
*/
int execute_rule_until(s_rule_until *rule);

/**
** @brief handle the while behavior
** @param rule containing the condition, and instructions
** @return
*/
int execute_rule_while(s_rule_while *rule);

/**
** @brief handle the case behavior
** @param rule containing the condition, and instructions
** @return
*/
int execute_rule_case(s_rule_case *rule);

void *execute_redirection(s_redirection *redirection);

#endif /* !EXECUTION */
