#include "dollar.h"

static s_tokens *lexArithmetic(char *cmd, int *index, s_tokens *token_list)
{
  char *str = NULL;
  int  c_braces_count = 0;
  int  i;

  for (i = 0; c_braces_count != 2; i++, (*index)++)
  {
    if (i % 64 == 0)
      str = realloc(str, (i + 65) * sizeof (char));

    // If reach end before double )
    if (getline_ps2(&cmd, index))
      continue;

    if (cmd[(*index)] == '\\' && cmd[(*index)] == ')')
      c_braces_count--;

    str[i] = cmd[(*index)];

    if (cmd[(*index)] == ')')
      c_braces_count++;
  }
  str[i] = '\0';

  token_list = token_add(str, TOK_ARITHMETIC, token_list);

  return token_list;
}


static s_tokens *lexVariable(char *cmd, int *index, s_tokens *token_list)
{
  char end_of_var = ' ';
  char *str = NULL;
  int  i;

  if (cmd[(*index) + 1] == '{')
    end_of_var = '}';

  for (i = 0; ; i++, (*index)++)
  {
    if (i % 64 == 0)
      str = realloc(str, (i + 65) * sizeof (char));

    if (end_of_var == ' ' && i != 1 &&
	(cmd[(*index)] == '\0' || cmd[(*index)] == ' ' ||
	 cmd[(*index)] == ':' || cmd[(*index)] == '-' || cmd[(*index)] == '+' ||
	 cmd[(*index)] == '=' || cmd[(*index)] == '?'))
	break;

    // If reach end before }
    if (getline_ps2(&cmd, index))
      continue;

    str[i] = cmd[(*index)];

    if (cmd[(*index)] == end_of_var)
      break;
  }

  (end_of_var == ' ') ? str[i] = '\0' : (str[i + 1] = '\0');
  (end_of_var == '}') ? (*index)++ : ((*index) = (*index));

  token_list = token_add(str, TOK_VARIABLE, token_list);

  return token_list;
}


s_tokens *lexDollar(char *cmd, int *index, s_tokens *token_list)
{
  char *str = NULL;

  if (cmd[(*index) + 1] == ' ' || cmd[(*index) + 1] == '\n' ||
      cmd[(*index) + 1] == '\0' || cmd[(*index) + 1] == '+' ||
      cmd[(*index) + 1] == '-' || cmd[(*index) + 1] == '=' ||
      cmd[(*index) + 1] == ':')
  {
    str = malloc(2 * sizeof (char));
    strncpy(str, "$", 2);
    (*index)++;
    token_list = token_add(str, TOK_WORD, token_list);
  }
  else if (cmd[(*index) + 1] == '(')
    if (cmd[(*index) + 2] == '(')
      return lexArithmetic(cmd, index, token_list);
    else
      // BONUS : call Command substitution
      for (; cmd[(*index)] == ')'; (*index)++)
	;
  else
    return lexVariable(cmd, index, token_list);

  return token_list;
}

