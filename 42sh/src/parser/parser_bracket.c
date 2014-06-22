#include "parser.h"

static char *get_closing_bracket(char *open_bracket)
{
  char *bracket = NULL;

  if (!IS_BRACKET(open_bracket))
    return NULL;

  bracket = malloc(sizeof (char) * 2);
  bracket[0] = (open_bracket[0] == '{') ? '}' : ')';
  bracket[1] = '\0';

  return bracket;
}

static void free_tabs(s_list *res, char *bracket)
{
  free(bracket);
  free_struct_list(res);
}

s_list *parse_bracket(s_tokens **token)
{
  s_list    *res = NULL;
  s_and_or  *and_or = NULL;
  char      *bracket;

  bracket = get_closing_bracket((*token)->token);
  if (bracket == NULL)
    return NULL;

  for (; *token && strcmp((*token)->token, bracket); and_or = NULL)
  {
    if (res != NULL && !(IS_SPECIAL_CHAR((*token)->token)))
    {
      free_tabs(res, bracket);
      return parse_error(*token);
    }
    /* To remove the ";" or "&" */
    if (res != NULL)
      *token = eat_token(*token);

    and_or = parse_and_or(token, 1);
    if (and_or == NULL)
    {
      free_tabs(res, bracket);
      return NULL;
    }
    list_add_element(&res, and_or);
  }

  free(bracket);
  return res;
}
