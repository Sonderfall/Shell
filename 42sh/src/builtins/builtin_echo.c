#include "builtins.h"
#include <math.h>

static int arg_zero(int i, char *argv)
{
  int acu = 2;
  int oct = 0;

  i++;

  while (acu >= 0 && argv[i] != '\0' && argv[i] >= 0 && argv[i] < 8)
  {
    oct += atoi(argv) * pow(8, acu);
    acu--;
    i++;
  }

  if (acu == -1)
  {
    if (oct < 0 || oct > 177)
      printf("?");
    else
      printf("%c", oct);
  }

  return 2 - acu;
}

static int arg_x(int i, char *argv)
{
  int acu = 1;
  int oct = 0;

  i++;

  while (acu >= 0 && argv[i] != '\0' && argv[i] >= 0 && argv[i] < 16)
  {
    oct += atoi(argv) * pow(16, acu);
    acu--;
    i++;
  }

  if (acu == -1)
  {
    if (oct < 0 || oct > 177)
      printf("?");
    else
      printf("%c", oct);
  }

  return 1 - acu;
}

static int arg_smallu(int i, char *argv)
{
  argv[i] = argv[i];

  /* FIXME */

  return 0;
}

static int arg_bigu(int i, char *argv)
{
  argv[i] = argv[i];

  /* FIXME */

  return 0;
}

static void print_simple(char argv)
{
  if (argv == 'a')
    printf("\a");

  if (argv == 'b')
    printf("\b");

  if (argv == 'e')
    printf("\027");

  if (argv == 'f')
    printf("\f");

  if (argv == 'n')
    printf("\n");

  if (argv == 'r')
    printf("\r");

  if (argv == 't')
    printf("\t");

  if (argv == 'v')
    printf("\v");

  if (argv == '\\')
    printf("\\");
}

static int print_not_simple(int i, char *argv)
{
  if (argv[i] == '0')
    return arg_zero(i, argv);

  if (argv[i] == 'x')
    return arg_x(i, argv);

  if (argv[i] == 'u')
    return arg_smallu(i, argv);

  if (argv[i] == 'U')
    return arg_bigu(i, argv);

  return 0;
}

static int print_option(char *argv)
{
  int i = 0;
  int slash = 0;

  while (argv[i] != '\0')
  {
    if (argv[i] == '\\')
    {
      slash = 1;
      i++;
      continue;
    }

    if (slash == 1)
    {
      if (argv[i] == 'c')
        return 1;

      print_simple(argv[i]);
      i += print_not_simple(i, argv);
      i++;
      continue;
    }

    i++;
    printf("%c", argv[i++]);
  }

  return 0;
}

static void print_arg(int argn, int acu, int argc, char *argv[])
{
  int c_arg = 0;

  for (; acu < argc && c_arg == 0; acu++)
  {
    if (argv[acu] == NULL)
      continue;

    if (argn == 0 || argn == 2 || argn == 3 || argn == 5)
      printf("%s", argv[acu]);

    if (argn == 1 || argn == 4)
      c_arg = print_option(argv[acu]);

    if (argn < 3 && c_arg == 0)
      printf("\n");

    if (argn >= 3 && c_arg == 0)
      printf(" ");

  }
}

static int is_arg(char *argv)
{
  int i = 1;

  if (argv == NULL || argv[0] != '-')
    return 0;

  while (argv[i] != '\0')
  {
    if (argv[i] != 'e' && argv[i] != 'E' && argv[i] != 'n')
      return 0;

    i++;
  }

  if (argv[i] == 'e')
    return 1;

  if (argv[i] == 'E')
    return 2;

  if (argv[i] == 'n')
    return 3;

  return -1;
}

static int main_echo(int argc, char *argv[])
{
  int argn = 0;
  int acu = 1;
  int arge = 0;

  if (argc == 1)
  {
    printf("\n");
    return 0;
  }

  while (is_arg(argv[acu]))
    if (is_arg(argv[acu++]) == 3)
      argn = 3;
    else
      arge = is_arg(argv[acu++]);

  argn += arge;
  print_arg(argn, acu, argc, argv);

  return 0;
}

int builtin_echo(s_simple_cmd *cmd)
{
  char **argv = NULL;
  int  pos = 0;
  int  res;

  argv = malloc(sizeof (char*) * (cmd->length_element + 1));
  for (size_t i = 0; i < cmd->length_element; ++i)
    if (cmd->element[i]->type == WORD)
      argv[pos++] = cmd->element[i]->element.word;

  res = main_echo(pos, argv);
  free(argv);
  return res;
}
