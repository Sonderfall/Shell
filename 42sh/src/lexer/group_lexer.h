#ifndef GROUP_LEXER_H
# define GROUP_LEXER_H

# include "string.h"

/**
** @brief Is_operator check if token can be an operator
** @param token The token to check if it is an operator or not
** @return 1 if is an ope, 0 otherwise
*/
int is_operator(char *token);

/**
** @brief check if the char c belongs to [0-9]
** @param c the character to check
** @return 1 if is an ope, 0 otherwise
*/
int belongs_number(char c);

/**
** @brief check if the char c belongs to [a-zA-Z]
** @param c the char to check
** @return 1 if is an ope, 0 otherwise
*/
int belongs_alpha(char c);

/**
** @brief check if the char c belongs to a list of simbols operator
** @param c the char to check
** @param flag the flag to separate the first occurence and the following
** @return 1 if is an ope, 0 otherwise
*/
int belongs_operator(char c, int flag);

/**
** @brief check if the char c belongs to a list of special char
** @param c the char to check
** @return 1 if is an ope, 0 otherwise
*/
int is_special_char(char c);

#endif /* !GROUP_LEXER_H */
