#include "group_lexer.h"
#include <stdio.h>

/*
** Is_operator check if token is an operator or can be an operator
** With flag = 0, check if token is an operator
** With flag = 1, check if it can be an operator
** return 1 if is an ope, 0 otherwise
*/
int is_operator(char *token)
{
  int  len;

  const char *operators[10] =
  {
    "&&", "||", ";;", "<<", ">>", "<&", ">&", "<>", "<<-", ">|"
  };

  len = strlen(token);

  for (int i = 0; i < 10; i++)
  {
    if (strncmp(token, operators[i], len) == 0)
      return 1;
  }

  return 0;
}


int belongs_operator(char c, int flag)
{
  const char first_ope[5] =
  {
    '&', '|', ';', '<', '>'
  };
  const char all_ope[6] =
  {
    '&', '|', ';', '<', '>', '-'
  };

  if (flag == 0)
  {
    for (int i = 0; i < 5; i++)
      if (first_ope[i] == c)
	return 1;
  }
  else
  {
    for (int i = 0; i < 6; i++)
      if (all_ope[i] == c)
	return 1;
  }

  return 0;
}

int belongs_number(char c)
{
  if (c >= '0' && c <= '9')
    return 1;
  else
    return 0;
}

int belongs_alpha(char c)
{
  if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '-'))
    return 1;
  else
    return 0;
}

/*
** Is called special char, characters who has to delimited a word
*/
int is_special_char(char c)
{
  if (c == '\n' || c == ';' || c == ' ' ||
      c == '\t' || c == '"' || c == '$')
    return 1;
  else
    return 0;
}
