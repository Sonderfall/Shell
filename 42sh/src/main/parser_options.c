#include "main.h"

int option_version(void)
{
  printf("Version 1.0\n");
  return 0;
}

int option_minusO(char *argv)
{
  /* TODO */
  argv = argv;
  return 0;
}

int option_plusO(char *argv)
{
  /* TODO */
  argv = argv;
  return 0;
}

int parse_args(int argc, char **argv)
{
  if (argc == 1)
    return loop_prompt();
  else
  {
    for (int i = 0; i < argc; ++i)
      if (!strcmp(argv[i], "--version"))
        return option_version();

    for (int i = 0; i < argc; ++i)
    {
      if (!strcmp(argv[i], "-c"))
        return run_once(argv[i + 1]);

      else if (!strcmp(argv[i], "-O"))
        return option_minusO(argv[i + 1]);

      else if (!strcmp(argv[i], "+O"))
        return option_plusO(argv[i + 1]);

      else if (!strcmp(argv[i], "--ast-print"))
        return loop_prompt_ast();

      else if (!strcmp(argv[i], "--norc"))
        return loop_prompt();
    }
  }

  print_error_cmd(argv[1]);
  exit(2);
}
