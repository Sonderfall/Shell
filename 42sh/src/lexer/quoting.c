#include "quoting.h"


static char *lex_single_quote(char *cmd,
			      int  *index_cmd,
			      char *token,
			      int  *index_tok)
{
  (*index_cmd)++;

  for (; cmd[(*index_cmd)] != '\''; (*index_cmd)++, (*index_tok)++)
  {
    if (((*index_tok) % 64) == 0)
      token = realloc(token, (64 + (*index_tok)) * sizeof (char));

    // If reach end before '
    if (getline_ps2(&cmd, index_cmd))
    {
      token[(*index_tok)] = '\n';
      continue;
    }

    token[(*index_tok)] = cmd[(*index_cmd)];
  }

  return token;
}


static char *lex_backslash(char *cmd,
			   int  *index_cmd,
			   char *token,
			   int  *index_tok)
{
  (*index_cmd)++;

  /* Ignoring the newline */
  if (token[(*index_tok)] != '\n')
    token[(*index_tok)] = cmd[(*index_cmd)];
  else
    (*index_tok)--;

  return token;
}


char *lex_quoting(char *cmd,
		  int  *index_cmd,
		  char *token,
		  int  *index_tok)
{
  if (cmd[(*index_cmd)] == '\\')
    return lex_backslash(cmd, index_cmd, token, index_tok);
  else
    return lex_single_quote(cmd, index_cmd, token, index_tok);
}

int is_quote_c(char c)
{
  if (c == '\\' || c == '\'')
    return 1;
  else
    return 0;
}
