#include "free_long_struct.h"
#include "free_rule.h"
#include "rule_case.h"
#include "shell_cmd.h"

s_shell_cmd *create_struct_shell_cmd(u_shell_command    cmd,
                                     e_type_shell_cmd   type)
{
  s_shell_cmd *res = NULL;

  if (NULL == cmd.list)
    return NULL;

  res = malloc(sizeof (s_shell_cmd));
  res->type = type;

  if (LIST == type)
    res->cmd.list = cmd.list;

  if (RULE_FOR == type)
    res->cmd.rule_for = cmd.rule_for;

  if (RULE_WHILE == type)
    res->cmd.rule_until = cmd.rule_until;

  if (RULE_UNTIL == type)
    res->cmd.rule_case = cmd.rule_case;

  if (RULE_IF == type)
    res->cmd.rule_if = cmd.rule_if;

  return res;
}

void free_struct_shell_cmd(s_shell_cmd *cmd)
{
  if (NULL == cmd)
    return;

  if (LIST == cmd->type)
    free_struct_list(cmd->cmd.list);

  if (RULE_FOR == cmd->type)
    free_rule_for(cmd->cmd.rule_for);

  if (RULE_WHILE == cmd->type)
    free_rule_while(cmd->cmd.rule_while);

  if (RULE_UNTIL == cmd->type)
    free_rule_until(cmd->cmd.rule_until);

  if (RULE_CASE == cmd->type)
    free_rule_case(cmd->cmd.rule_case);

  if (RULE_IF == cmd->type)
    free_rule_if(cmd->cmd.rule_if);
  free(cmd);
}
