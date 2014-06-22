#include "builtins.h"

static void change_pwd(void)
{
  char *new_pwd;

  new_pwd = get_current_dir_name();
  setenv("PWD", new_pwd, 1);
  free(new_pwd);
}

static int ch_dir(const char *new_pwd, char *old_pwd)
{
  int res = 1;

  res = chdir(new_pwd);

  if (res == -1)
  {
    printf("bash : cd: %s: No such file or directory\n",
           new_pwd);
    free(old_pwd);
    return 1;
  }
  setenv("OLDPWD", old_pwd, 1);
  change_pwd();
  free(old_pwd);
  return 0;
}

static char *get_pwd(void)
{
  int  length = 0;
  char *res = NULL;

  length = strlen(getenv("PWD")) + 1;
  res = malloc(sizeof (char) * length);

  strncpy(res, getenv("PWD"), length);

  return res;
}

int builtin_cd(s_simple_cmd *cmd)
{
  char *old_pwd = NULL;

  old_pwd = get_pwd();
  if (cmd->length_element == 1)
    return ch_dir(getenv("HOME"), old_pwd);

  else if (cmd->element[1] != NULL)
    return ch_dir(cmd->element[1]->element.word, old_pwd);

  return 1;
}
