#include "parser.h"

s_prefix *parse_prefix(s_tokens **token)
{
  s_prefix          *res = NULL;
  u_uprefix         prefix;
  int               length;
  e_type_element    type;

  if (IS_REDIRECTION((*token)->token))
  {
    prefix.redirect = parse_redirection(token);
    type = REDIRECTION;
  }
  else
  {
    length = strlen((*token)->token);
    prefix.word = malloc(sizeof (char) * (length + 1));
    strncpy(prefix.word, (*token)->token, length + 1);
    *token = eat_token(*token);
    type = WORD;
  }

  res = create_prefix(prefix, type);

  return res;
}

s_element *parse_element(s_tokens **token)
{
  s_element         *res = NULL;
  u_uelement        element;
  int               length;
  e_type_element    type;

  if (IS_REDIRECTION((*token)->token))
  {
    element.redirect = parse_redirection(token);
    type = REDIRECTION;
  }
  else
  {
    length = strlen((*token)->token);
    element.word = malloc(sizeof (char) * (length + 1));
    strncpy(element.word, (*token)->token, length + 1);
    *token = eat_token(*token);
    type = WORD;
  }

  res = create_element(element, type);
  if (type == WORD)
    free(element.word);

  return res;
}
