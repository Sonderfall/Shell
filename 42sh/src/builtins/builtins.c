#include "builtins.h"

int is_builtins(s_simple_cmd *cmd)
{
  int  res = -1;

  if (cmd->element != NULL)
  {
    if (!strcmp(cmd->element[0]->element.word, "cd"))
      res = builtin_cd(cmd);

    else if (!strcmp(cmd->element[0]->element.word, "source"))
      res = builtin_source(cmd);

    else if (!strcmp(cmd->element[0]->element.word, "echo"))
     res = builtin_echo(cmd);

    else if (!strcmp(cmd->element[0]->element.word, "export"))
      res = builtin_export(cmd);

    else if (!strcmp(cmd->element[0]->element.word, "exit"))
      res = builtin_exit(cmd);
  }

  return res;
}


