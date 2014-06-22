#ifndef PARSER_H
# define PARSER_H

# include "../lexer/lexer.h"
# include "../ast/ast.h"

/**
** @brief print the token which cause a parse error
** @param token token causing a problem
** @return NULL
*/
void            *parse_error(s_tokens *token);

/**
** @brief parse a list of token
** @param token pointer to the current token
** @return an ast starting with a s_list
*/
s_list          *parse_list(s_tokens **token);

/**
** @brief parse a list of and or condition
** @param token pointer to the current token
** @param is_first first command of the and or
** @return an ast starting with a s_and_or
*/
s_and_or        *parse_and_or(s_tokens **token, int is_first);

/**
** @brief parse a list of pipe command
** @param token pointer to the current token
** @return an ast starting from a pipeline of command
*/
s_pipeline      *parse_pipeline(s_tokens **token);


/**
** @brief parse a single command
** @param token pointer to the current token
** @return an ast starting from a single command
*/
s_cmd           *parse_command(s_tokens **token);

/**
** @brief parse a shell command
** @param token pointer to the current token
** @return an ast starting from a shell command
*/
s_shell_cmd     *parse_shell_command(s_tokens **token);

/**
** @brief parse a function command
** @param token pointer to the current token
** @return an ast starting from a function command
*/
s_funcdec       *parse_funcdec(s_tokens **token);

/**
** @brief parse a simple command
** @param token pointer to the current token
** @return an ast starting from a simple command
*/
s_simple_cmd    *parse_simple_command(s_tokens **token);

/**
** @brief parse a group of command inside bracket
** @param token pointer to the current token
** @return an ast starting from a group of command
*/
s_list          *parse_bracket(s_tokens **token);

/**
** @brief parse a simple command
** @param token pointer to the current token
** @return an ast starting from a simple command
*/
s_simple_cmd    *parse_simple_command(s_tokens **token);

/**
** @brief parse a rule for
** @param token pointer to the current token
** @return an ast starting from a rule for
*/
s_rule_for      *parse_rule_for(s_tokens **token);

/**
** @brief parse a while rule
** @param token pointer to the current token
** @return an ast starting from the rule while
*/
s_rule_while    *parse_rule_while(s_tokens **token);

/**
** @brief parse a rule until
** @param token pointer to the current token
** @return an ast starting from a rule until
*/
s_rule_until    *parse_rule_until(s_tokens **token);

/**
** @brief parse a rule case
** @param token pointer to the current token
** @return an ast starting from a rule case
** @note Not yet implemented
*/
s_rule_case     *parse_rule_case(s_tokens **token);

/**
** @brief create an if rule
** @param token token from the lexer
** @return if rule token
*/
s_rule_if       *parse_rule_if(s_tokens **token);

/**
** @brief parse a do group of commands
** @param token pointer to the current token
** @return an ast starting from a list of command
*/
s_list          *assign_do_group(s_tokens **token);

/**
** @brief parse a redirection
** @param token pointer to the current token
** @return an ast starting from a redirection
*/
s_redirection   *parse_redirection(s_tokens **token);

/**
** @brief add a word or a redirection to the ast
** @param token pointer to the current token
** @return an ast containing either a word of a redirection
*/
s_prefix *parse_prefix(s_tokens **token);

/**
** @brief add a word or a redirection to the ast
** @param token pointer to the current token
** @return an ast containing either a word of a redirection
*/
s_element *parse_element(s_tokens **token);

#endif /* !PARSER_H */

