#include "free_long_struct.h"
#include "free_struct.h"
#include "shell_cmd.h"
#include "union.h"

void free_struct_funcdec(s_funcdec *funcdec)
{
  if (NULL == funcdec)
    return;

  free_struct_shell_cmd(funcdec->cmd);
  free(funcdec->name);
  free(funcdec);
}

void free_struct_and_or(s_and_or *and_or)
{
  if (NULL == and_or)
    return;

  free_struct_pipeline(and_or->pipeline);
  free_struct_and_or(and_or->next);
  free(and_or);
}

void free_struct_cmd(s_cmd *cmd)
{
  if (NULL == cmd)
    return;

  if (SIMPLE_COMMAND == cmd->type)
    free_struct_simple_cmd(cmd->cmd.simple_cmd);

  if (SHELL_COMMAND == cmd->type)
    free_struct_shell_cmd(cmd->cmd.shell_cmd);

  if (FUNCDEC == cmd->type)
    free_struct_funcdec(cmd->cmd.funcdec);

  free(cmd);
}

void free_struct_redirection(s_redirection *redirect)
{
  if (NULL == redirect)
    return;

  free(redirect->word);
  free(redirect);
}
