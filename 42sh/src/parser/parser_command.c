#define _BSD_SOURCE
#include "parser.h"

s_cmd *parse_command(s_tokens **token)
{
  s_cmd             *res = NULL;
  e_command_type    type = NO_TYPE;
  u_command         cmd;

  if (!*token)
    return NULL;

  if (IS_SHELL_CMD((*token)->token))
  {
    cmd.shell_cmd = parse_shell_command(token);
    type = SHELL_COMMAND;
  }
  else if (IS_FUNCDEC(*token))
  {
    cmd.funcdec = parse_funcdec(token);
    type = FUNCDEC;
  }
  else
  {
    cmd.simple_cmd = parse_simple_command(token);
    type = SIMPLE_COMMAND;
  }

  if (cmd.shell_cmd == NULL)
    return NULL;

  res = create_cmd(cmd, type);

  return res;
}
s_funcdec *parse_funcdec(s_tokens **token)
{
  s_funcdec     *res = NULL;
  s_shell_cmd   *cmd = NULL;
  int           length;
  char          *name;

  if (!strcmp((*token)->token, "function"))
    *token = eat_token(*token);

  length = strlen((*token)->token);
  name = malloc(sizeof (char) * (length + 1));
  strncpy(name, (*token)->token, length + 1);

  *token = eat_token(*token);
  cmd = parse_shell_command(token);
  if (cmd == NULL)
  {
    free(name);
    return NULL;
  }

  res = create_funcdec(name, cmd);
  free(name);

  return res;
}

static void set_shell_cmd(s_tokens          **token,
                          u_shell_command   *cmd,
                          e_type_shell_cmd  *type)
{
  if (!strcmp((*token)->token, "for"))
  {
    cmd->rule_for = parse_rule_for(token);
    *type = RULE_FOR;
  }
  else if (!strcmp((*token)->token, "case"))
  {
    cmd->rule_case = parse_rule_case(token);
    *type = RULE_CASE;
  }
  else if (IS_BRACKET((*token)->token))
  {
    cmd->list = parse_bracket(token);
    *type = LIST;
  }
}

static void set_shell_command(s_tokens          **token,
                              u_shell_command   *cmd,
                              e_type_shell_cmd  *type)
{
  if (!strcmp((*token)->token, "until"))
  {
    cmd->rule_until = parse_rule_until(token);
    *type = RULE_UNTIL;
  }
  else if (!strcmp((*token)->token, "while"))
  {
    cmd->rule_while = parse_rule_while(token);
    *type = RULE_WHILE;
  }
  else if (!strcmp((*token)->token, "if"))
  {
    cmd->rule_if = parse_rule_if(token);
    *type = RULE_IF;
  }
  else
    set_shell_cmd(token, cmd, type);
}

s_shell_cmd *parse_shell_command(s_tokens **token)
{
  s_shell_cmd       *res = NULL;
  u_shell_command   cmd;
  e_type_shell_cmd  type;

  if (!*token)
    return NULL;

  cmd.list = NULL;
  set_shell_command(token, &cmd, &type);

  if (cmd.list == NULL)
    return NULL;

  res = create_struct_shell_cmd(cmd, type);

  return res;
}

s_simple_cmd *parse_simple_command(s_tokens **token)
{
  s_simple_cmd      *res = NULL;
  s_prefix          *prefix = NULL;
  s_element         *element = NULL;

  for (; *token && !EXIT_SIMPLE_CMD((*token)->token);)
  {
    prefix = NULL;
    element = NULL;

    if (IS_ASSIGNEMENT_WORD((*token)->token) &&
	(res == NULL || res->length_element == 0))
      prefix = parse_prefix(token);
    else
      element = parse_element(token);

    /* Both are at NULL */
    if (prefix == NULL && element == NULL)
    {
      free_struct_simple_cmd(res);
      return NULL;
    }
    simple_cmd_add_element(&res, prefix, element);
  }

  return res;
}
