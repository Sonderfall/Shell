#include "builtins.h"

static int p_option(void)
{
  int         i = 0;
  extern char **environ;

  while (environ[i] != NULL)
  {
    printf("declare -x %s\n", environ[i]);
    i++;
  }

  return 0;
}

int builtin_export(s_simple_cmd *cmd)
{
  if (cmd->element[1] == NULL ||
      !strcmp(cmd->element[1]->element.word, "-p"))
    return p_option();

  else if (cmd->element[1] != NULL &&
           !strcmp(cmd->element[1]->element.word, "-n") &&
           (cmd->element[2] == NULL))
    return p_option();

  else if (cmd->element[1] != NULL &&
           !strcmp(cmd->element[1]->element.word, "-n") &&
           (cmd->element[2] != NULL))
    return unsetenv(cmd->element[2]->element.word);

  else if (cmd->element[1] != NULL)
    return setenv(cmd->element[1]->element.word, "", 1);

  else if (cmd->prefix[0] != NULL)
    return putenv(cmd->prefix[0]->prefix.word);

  return 0;
}
