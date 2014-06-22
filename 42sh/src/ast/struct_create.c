#include "struct_create.h"

s_and_or *create_and_or(s_pipeline *pipeline, e_and_or_type type)
{
  s_and_or *res = NULL;

  if (NULL == pipeline)
    return NULL;

  res = malloc(sizeof (s_and_or));
  res->connection = type;
  res->pipeline = pipeline;
  res->next = NULL;

  return res;
}

s_cmd *create_cmd(u_command command, e_command_type type)
{
  s_cmd *res = NULL;

  if (NULL == command.funcdec)
    return NULL;

  res = malloc(sizeof (s_cmd));
  res->type = type;

  if (SIMPLE_COMMAND == type)
    res->cmd.simple_cmd = command.simple_cmd;

  if (SHELL_COMMAND == type)
    res->cmd.shell_cmd = command.shell_cmd;

  if (FUNCDEC == type)
    res->cmd.funcdec = command.funcdec;

  return res;
}

s_redirection *create_redirection(char       *word,
                                  e_redirect type,
                                  int        ionumber)
{
  s_redirection *res = NULL;
  int           length = 0;

  if (NULL == word)
    return NULL;

  length = strlen(word);
  res = malloc(sizeof (s_redirection));
  res->ionumber = ionumber;
  res->type = type;
  /* We can free word afterward */
  res->word = malloc(sizeof (char) * (length + 1));
  strncpy(res->word, word, length + 1);

  return res;
}

s_funcdec *create_funcdec(char *name, s_shell_cmd *cmd)
{
  s_funcdec *res = NULL;
  int       length = 0;

  if (NULL == name || NULL == cmd)
    return NULL;

  res = malloc(sizeof (s_funcdec));
  length = strlen(name);
  res->name = malloc(sizeof (char) * (length + 1));
  strncpy(res->name, name, length + 1);
  res->cmd = cmd;

  return res;
}
