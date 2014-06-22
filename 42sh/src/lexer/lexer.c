#define _BSD_SOURCE
#include "lexer.h"

static s_tokens *lexOperator(char     *cmd,
                             int      *index,
                             s_tokens *token_list)
{
  int  j;
  char *token = NULL;

  for (j = 0; cmd[(*index)] != '\0'; j++, (*index)++)
  {
    token = (((j % 64) == 0) ? realloc(token, (65 + j)) : token);

    if (belongs_operator(cmd[(*index)], 1))
    {
      token[j] = cmd[(*index)];
      token[j + 1] = '\0';

      if (is_operator(token) == 0)
      {
	token[j] = '\0';
	break;
      }
    }
    else
      break;
  }

  token_list = token_add(token, TOK_OPERATOR, token_list);

  return token_list;
}

static s_tokens *lexNumber(char     *cmd,
                           int      *index,
			   s_tokens *token_list)
{
  int  j;
  char *token = NULL;

  for (j = 0; cmd[(*index)] != '\0'; j++, (*index)++)
  {
    if ((j % 64) == 0)
      token = realloc(token, (65 + j) * sizeof (char));

    if (belongs_number(cmd[(*index)]) == 1)
      token[j] = cmd[(*index)];
    else
      break;
  }

  token[j] = '\0';
  token_list = token_add(token, TOK_NUMBER, token_list);

  return token_list;
}

static s_tokens *lexWord(char     *cmd,
                         int      *index,
			 s_tokens *token_list)
{
  int  j;
  char *token = NULL;

  for (j = 0; cmd[(*index)] != '\0'; j++, (*index)++)
  {
    if ((j % 64) == 0)
      token = realloc(token, (65 + j) * sizeof (char));

    if (!is_special_char(cmd[(*index)]) && !belongs_operator(cmd[(*index)], 0))
      if (is_quote_c(cmd[(*index)]) == 1)
	token = lex_quoting(cmd, index, token, &j);
      else
	token[j] = cmd[(*index)];
    else
      break;
  }

  token[j] = '\0';
  token_list = token_add(token, TOK_WORD, token_list);

  return token_list;
}

static s_tokens *lexSpecial(char *cmd, int *index, s_tokens *token_list)
{
  char *str = NULL;

  if (cmd[(*index)] == '\n' || cmd[(*index)] == ';')
  {
    str = malloc(2 * sizeof (char));
    str[0] = cmd[(*index)];
    str[1] = '\0';

    if (str[0] == '\n')
      token_list = token_add(str, TOK_NEWLINE, token_list);
    else
      token_list = token_add(str, TOK_SEMICOLON, token_list);
  }

  (*index)++;

  return token_list;
}

static s_tokens *lexDQuote(char *cmd, int *index, s_tokens *token_list)
{
  int  j;
  char *token = NULL;

  (*index)++;
  for (j = 0; cmd[(*index)] != '"'; (*index)++, j++)
  {
    if ((j % 64) == 0)
      token = realloc(token, ((65 + j) * sizeof (char)));

    // If reach end before "
    if (getline_ps2(&cmd, index))
    {
      token[j] = '\n';
      continue;
    }

    if (cmd[(*index)] == '\\')
    {
      token[j] = cmd[(*index)];
      *index += 1;
    }

    token[j] = cmd[(*index)];
  }

  token[j] = '\0';
  (*index)++;
  if (token != NULL)
    token_list = token_add(token, TOK_D_QUOTE, token_list);

  return token_list;
}


s_tokens *lexer(char *cmd)
{
  s_tokens *token_list = NULL;
  int      index;

  if (cmd != NULL)
    for (index = 0; cmd[index] != '\0'; )
    {
      if (cmd[index] == '#')
	for (; cmd[index] != '\n' && cmd[index] != '\0'; index++)
	  ;

      if (cmd[index] == '$')
	token_list = lexDollar(cmd, &index, token_list);

      else if (cmd[index] == '"')
	token_list = lexDQuote(cmd, &index, token_list);

      else if (belongs_operator(cmd[index], 0) == 1)
        token_list = lexOperator(cmd, &index, token_list);

      else if (belongs_number(cmd[index]) == 1)
        token_list = lexNumber(cmd, &index, token_list);

      else if (is_special_char(cmd[index]) == 1)
        token_list = lexSpecial(cmd, &index, token_list);

      /* Default : Is a word */
      else
        token_list = lexWord(cmd, &index, token_list);
    }

  return token_list;
}
