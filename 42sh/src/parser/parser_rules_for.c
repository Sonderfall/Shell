#include "parser.h"
#include <stdio.h>

static char *assign_name(s_tokens **token)
{
  char *name = NULL;
  int  length;

  if (*token == NULL || (*token)->token == NULL)
    return NULL;

  length = strlen((*token)->token);
  name = malloc(sizeof (char) * (length + 1));

  strncpy(name, (*token)->token, length);

  return name;
}

static char **assign_in(s_tokens **token, size_t *size)
{
  char  **res = NULL;
  int   length;

  for (*size = 0; *token != NULL && !EXIT_DO_CONDITION((*token)->token);
       *token = eat_token(*token))
  {
    res = realloc(res, sizeof (char *) * ++(*size));
    length = strlen((*token)->token);
    res[*size - 1] = malloc(sizeof (char) * (length + 1));
    strncpy(res[*size - 1], (*token)->token, length);
  }

  return res;
}

static void add_to_list(s_and_or        **head,
                        s_and_or        **tail,
                        s_pipeline      *pipeline,
                        s_tokens        **token)
{
  s_and_or *var = NULL;

  if (IS_AND((*token)->token))
    var = create_and_or(pipeline, AND);
  else if (IS_OR((*token)->token))
    var = create_and_or(pipeline, OR);
  else
    var = create_and_or(pipeline, NONE);

  if (*tail == NULL)
    *tail = var;
  else
    (*tail)->next = var;
  *tail = var;
  if (*head == NULL)
    *head = *tail;
  else if ((*head)->next == NULL)
    (*head)->next = *tail;
}

static void *free_and_exit_error(s_and_or *res)
{
  free_struct_and_or(res);
  return NULL;
}

static s_and_or *assign_line(s_tokens **token)
{
  s_and_or      *res = NULL;
  s_and_or      *tmp = NULL;
  s_pipeline    *pipeline = NULL;

  for (; *token != NULL && strcmp((*token)->token, "\n");
      *token = eat_token(*token))
  {
    pipeline = NULL;
    while (*token != NULL && !(EXIT_PIPELINE((*token)->token)) &&
          strcmp((*token)->token, "\n") && !EXIT_DO_GROUP((*token)->token))
    {
      pipeline_add_element(&pipeline, parse_command(token));
      if (pipeline == NULL)
        return free_and_exit_error(res);
    }
    if (EXIT_DO_GROUP((*token)->token))
      return res;

    if (*token == NULL)
      return free_and_exit_error(res);

    add_to_list(&res, &tmp, pipeline, token);
  }

  return res;
}

s_list *assign_do_group(s_tokens **token)
{
  s_list    *res = NULL;
  s_and_or  *and_or = NULL;

  for (; *token && !EXIT_DO_GROUP((*token)->token); and_or = NULL)
  {
    and_or = assign_line(token);
    if (NULL == and_or)
    {
      free_struct_list(res);
      return NULL;
    }
    list_add_element(&res, and_or);
  }

  return res;
}

s_rule_for *parse_rule_for(s_tokens **token)
{
  s_rule_for    *res = NULL;
  s_shell_cmd   *cmd;
  size_t        length;

  if (strcmp((*token)->token, "for"))
    return NULL;

  *token = eat_token(*token);

  res->name = assign_name(token);
  if (!strcmp((*token)->token, "in"))
  {
    res->in = assign_in(token, &length);
    res->length_in = length;
  }
  else
  {
    res->in = NULL;
    res->length_in = 0;
  }
  *token = eat_token(*token);
  cmd = parse_shell_command(token);
  if (cmd == NULL)
    return NULL;

  return res;
}
