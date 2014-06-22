#include "parser.h"

s_list *parse_list(s_tokens **token)
{
  s_list    *res = NULL;
  s_and_or  *and_or = NULL;

  for (; *token != NULL; and_or = NULL)
  {
    if (res != NULL && !(IS_SPECIAL_CHAR((*token)->token)))
    {
      free_struct_list(res);
      return parse_error(*token);
    }
    /* To remove the ";" or "&" */
    if (res != NULL)
      *token = eat_token(*token);

    /* the "Special character was the last one */
    if (!*token)
      break;
    and_or = parse_and_or(token, 1);
    if (and_or == NULL)
    {
      free_struct_list(res);
      return NULL;
    }
    list_add_element(&res, and_or);
  }

  return res;
}

static s_and_or *parse_next_and_or(s_tokens **token, s_pipeline *pipeline)
{
  s_and_or      *res = NULL;
  s_and_or      *tmp = NULL;
  e_and_or_type type;

  if (!*token || EXIT_AND_OR((*token)->token))
    return create_and_or(pipeline, NONE);
  type = (IS_AND((*token)->token)) ? AND : (IS_OR((*token)->token)) ? OR :
    NONE;
  res = create_and_or(pipeline, type);
  tmp = parse_and_or(token, 0);
  if (tmp == NULL)
  {
    free_struct_and_or(res);
    return NULL;
  }
  res->next = tmp;

  return res;
}

s_and_or *parse_and_or(s_tokens **token, int is_first)
{
  s_pipeline    *pipeline = NULL;

  if (!is_first && !IS_AND_OR((*token)->token))
    return parse_error(*token);

  /* Remove the token "&&" or "||" */
  if (!is_first)
    *token = eat_token(*token);

  pipeline = parse_pipeline(token);
  if (pipeline == NULL)
    return NULL;

  return parse_next_and_or(token, pipeline);
}

s_pipeline *parse_pipeline(s_tokens **token)
{
  s_pipeline    *res = NULL;
  s_cmd         *cmd = NULL;

  for (; *token && !EXIT_PIPELINE((*token)->token); cmd = NULL)
  {
    if (res != NULL && !IS_PIPELINE((*token)->token))
    {
      free_struct_pipeline(res);
      return parse_error(*token);
    }
    if (res != NULL)
      /* Get the start of the next command */
      *token = eat_token(*token);
    *token = get_next_line(*token);
    cmd = parse_command(token);
    if (cmd == NULL)
    {
      free_struct_pipeline(res);
      return NULL;
    }
    pipeline_add_element(&res, cmd);
  }

  return res;
}
