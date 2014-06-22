#include "parser.h"

s_rule_while *parse_rule_while(s_tokens **token)
{
  s_rule_while *res = NULL;
  s_and_or     *condition = NULL;
  s_list       *group = NULL;

  if (strcmp((*token)->token, "while"))
    return NULL;

  *token = eat_token(*token);
  condition = parse_and_or(token, 1);

  if (*token && !strcmp((*token)->token, ";"))
    *token = eat_token(*token);

  if (NULL == condition || !*token || !EXIT_DO_CONDITION((*token)->token))
  {
    free_struct_and_or(condition);
    return NULL;
  }
  *token = eat_token(*token);

  group = assign_do_group(token);

  if (NULL == group || (*token && !EXIT_DO_GROUP((*token)->token)))
  {
    free_struct_and_or(condition);
    free_struct_list(group);
    return NULL;
  }
  res = create_rule_while(condition, group);
  *token = eat_token(*token);

  return res;
}

s_rule_until *parse_rule_until(s_tokens **token)
{
  s_rule_until *res = NULL;
  s_and_or     *condition = NULL;
  s_list       *group = NULL;

  if (strcmp((*token)->token, "until"))
    return NULL;

  *token = eat_token(*token);
  condition = parse_and_or(token, 1);

  if (NULL == condition || !*token || !EXIT_DO_CONDITION((*token)->token))
  {
    free_struct_and_or(condition);
    return NULL;
  }
  *token = eat_token(*token);

  group = assign_do_group(token);

  if (NULL == group || (*token && !EXIT_DO_GROUP((*token)->token)))
  {
    free_struct_and_or(condition);
    free_struct_list(group);
    return parse_error(*token);
  }
  res = create_rule_until(group, condition);
  *token = eat_token(*token);

  return res;
}

static s_list *assign_action(s_tokens **token)
{
  s_and_or *and_or;
  s_list   *res = NULL;

  for (; *token && !EXIT_IF_GROUP((*token)->token); and_or = NULL)
  {
    if (res != NULL && strcmp((*token)->token, ";") &&
        strcmp((*token)->token, "&"))
      parse_error(*token);

    if (res != NULL)
      *token = eat_token(*token);

    if (*token && EXIT_IF_GROUP((*token)->token))
      break;

    and_or = parse_and_or(token, 1);

    if (NULL == and_or)
      return NULL;

    list_add_element(&res, and_or);
  }

  return res;

}

static s_rule_if *parse_else(s_tokens   **token,
                             s_and_or   *condition,
                             s_list     *action)
{
  s_list            *elseif = NULL;
  s_pipeline        *pipeline = NULL;
  u_command         cmd;
  u_shell_command   ifcondition;


  if (!*token || !strcmp((*token)->token, "fi"))
    return create_rule_if(condition, action, elseif);

  if (!strcmp((*token)->token, "elif"))
  {
    strncpy((*token)->token, "if\0", 3);
    ifcondition.rule_if = parse_rule_if(token);
    if (ifcondition.rule_if == NULL)
      return NULL;
    cmd.shell_cmd = create_struct_shell_cmd(ifcondition, RULE_IF);
    pipeline_add_element(&pipeline, create_cmd(cmd, SHELL_COMMAND));
    list_add_element(&elseif, create_and_or(pipeline, NONE));
  }

  if (!strcmp((*token)->token, "else"))
  {
    *token = eat_token(*token);
    elseif = assign_action(token);
  }

  return create_rule_if(condition, action, elseif);
}

s_rule_if *parse_rule_if(s_tokens **token)
{
  s_and_or   *condition =  NULL;
  s_list     *action =  NULL;

  if (strcmp((*token)->token, "if"))
    return NULL;

  *token = eat_token(*token);

  condition = parse_and_or(token, 1);
  *token = eat_token(*token);
  if (condition == NULL || !*token || !EXIT_IF_CONDITION((*token)->token))
  {
    free_struct_and_or(condition);
    return NULL;
  }

  *token = eat_token(*token);

  action = assign_action(token);

  if (action == NULL || (*token && !EXIT_IF_GROUP((*token)->token)))
  {
    free_struct_and_or(condition);
    free_struct_list(action);
    return parse_error(*token);
  }

  *token = eat_token(*token);
  return parse_else(token, condition, action);
}
