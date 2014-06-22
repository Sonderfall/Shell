#include "builtin_alias.h"

static void record_arg(char *argv)
{
  /* FIXME by registering argv*/

  argv = argv;
}

static int check_arg(int argc, char *argv[])
{
  int  acu = 2;
  int  arg = 0;
  int  acc = 1;

  while (acu < argc)
  {
    if (argv[1][0] == '-')
    {
      arg = 1;

      while (argv[1][acc] != '\0' && argv[1][acc] == 'p')
        acc++;

      continue;
    }

    if (argv[1][acc] != '\0' && argv[1][0] == '-')
      return -1;

    record_arg(argv[acu]);

    if (arg < 10)
      arg += 10;

    acu++;
  }

  return arg;
}

int builtin_alias(int argc, char *argv[])
{
  int  arg = 0;
  FILE *file;
  char line[512];

  file = fopen("~/.42shrc", "r");

  if (file == NULL)
    return 0;

  arg = check_arg(argc, argv);

  while (fgets(line, 512, file) != NULL && arg < 2)
  {
    if (arg == 1)
      printf("alias ");

    printf("%s", line);
  }

  fclose(file);

  return 0;
}
