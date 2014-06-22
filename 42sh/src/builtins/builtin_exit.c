#include "builtins.h"
#include <ctype.h>

static int my_strlen(const char *s)
{
  if (*s)
    return 1 + my_strlen(s + 1);
  else
    return 0;
}

static int is_number(char *str)
{
  for (int i = 0; i < my_strlen(str); i++)
    if (isdigit(str[i]))
      return 0;

  return 1;
}

int builtin_exit(s_simple_cmd *cmd)
{
  int n = 0;

  printf("exit\n");
  if (cmd->length_element >= 3 &&
      is_number(cmd->element[1]->element.word))
    printf("42sh: exit: too many arguments\n");

  else if (cmd->length_element == 2 &&
           is_number(cmd->element[1]->element.word))
  {
    n = atoi(cmd->element[1]->element.word);
    return (n % 256) - 500;
  }
  else if (cmd->length_element == 2 &&
           !is_number(cmd->element[1]->element.word))
  {
    printf("42sh: exit: %s: numeric argument required\n",
           cmd->element[1]->element.word);
    return 255 - 500;
  }

  else if (cmd->length_element == 1)
    return -500;

  return 0;
}
