#include "parser.h"
#include <unistd.h>

static e_redirect get_specific_redirection(s_tokens **token)
{
  if (!strcmp((*token)->token, ">"))
    return SIMPLE_CHEVRON_RIGHT;
  else if (!strcmp((*token)->token, ">>"))
    return DOUBLE_CHEVRON_RIGHT;
  else if (!strcmp((*token)->token, "<"))
    return SIMPLE_CHEVRON_LEFT;
  else if (!strcmp((*token)->token, ">>"))
    return DOUBLE_CHEVRON_LEFT;
  else if (!strcmp((*token)->token, "<<-"))
    return CHEVRON_HYPHEN;
  else if (!strcmp((*token)->token, ">&"))
    return AMPERSAND_CHEVRON_RIGHT;
  else if (!strcmp((*token)->token, "<&"))
    return AMPERSAND_CHEVRON_LEFT;
  else if (!strcmp((*token)->token, "<>"))
    return CHEVRON_LEFT_RIGHT;
  else
    return CHEVRON_PIPE;

}

s_redirection *parse_redirection(s_tokens **token)
{
  s_redirection *res = NULL;
  int           ionumber = STDOUT_FILENO;
  e_redirect    type;

  if (!IS_REDIRECTION((*token)->token))
  {
    ionumber = atoi((*token)->token);
    *token = eat_token(*token);
  }

  if (!*token || !IS_REDIRECTION((*token)->token))
  {
    parse_error(*token);
    return NULL;
  }
  type = get_specific_redirection(token);
  *token = eat_token(*token);
  res = create_redirection((*token)->token, type, ionumber);
  *token = eat_token(*token);

  return res;
}
