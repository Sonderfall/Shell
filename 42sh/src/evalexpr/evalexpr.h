#ifndef EVALEXPR_H
# define EVALEXPR_H

# include <ctype.h>
# include "../variable/variable.h"


typedef union data
{
  int end;
  struct ast *expr[2];
} u_data;

typedef struct ast
{
  char      op;
  u_data    data;
} s_ast;

/**
** @brief parse expresion arithmetic
** @param string string to evaluate
** @param pos position on the expression
** @return an ast for the expresiont
*/
s_ast *create_expression(const char *string, int *pos);

/**
** @brief return the value of the arithmetic expression
** @param expr expression to work on
** @return value of the expression
*/
int evaluate_expresion(s_ast *expr);

#endif /* !EVALEXPR_H */
