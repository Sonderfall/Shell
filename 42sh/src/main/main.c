#include "main.h"

s_global g_global;

void print_error_cmd(char *cmd)
{
  printf("42sh: %s: invalid option\n", cmd);
  printf("Usage:  42sh [GNU long option] [option] ...\n");
  printf("  42sh [GNU long option] [option] script-file ...\n");
  printf("GNU long options:\n");
  printf("  --version\n");
  printf("  --ast-print\n");
  printf("  --norc\n");
  printf("Shell options:\n");
  printf("  -irsD or -c command or -O shopt_option");
  printf("                 (invocation only)\n");
  printf("  -abefhkmnptuvxBCHP or -o option\n");
}

static int treat_grammar(s_list *list, char *buff)
{
  int  res;
  char *value;

  res = execute_list(list);
  free_struct_list(list);
  free(buff);
  value = itoa(res);

  add_var("?", value);
  free(value);
  printf("\n");

  return res;
}

int loop_prompt(void)
{
  char      *buff = NULL;
  s_tokens  *token;
  s_list    *list;
  int       res = 0;

  while (1)
  {
    buff = readline("PS1");
    token = lexer(buff);
    if (token == NULL)
      continue;
    list = parse_list(&token);
    if (list == NULL)
    {
      while (token)
        token = eat_token(token);
      continue;
    }

    res = treat_grammar(list, buff);

    if (res < -230)
      return res + 500;
  }
  return res;
}


int loop_prompt_ast(void)
{
  char      *buff = NULL;
  s_tokens  *token;
  s_list    *list;
  int       res = 0;

  while (1)
  {
    buff = readline("PS1");
    token = lexer(buff);
    if (token == NULL)
      continue;
    list = parse_list(&token);
    if (list == NULL)
    {
      while (token)
        token = eat_token(token);
      continue;
    }
    create_ast_dot(list);
    res = treat_grammar(list, buff);

    if (res < -230)
      return res + 500;
  }

  return res;
}

int run_once(char *cmd)
{
  s_tokens *tok = NULL;
  s_list   *list = NULL;
  int      res = 0;

  tok = lexer(cmd);
  list = parse_list(&tok);

  res = execute_list(list);
  free_struct_list(list);

  return res;
}

int main(int argc, char **argv)
{
  int    c;
  char   *buff = NULL;
  int    res;

  add_var("0", basename(argv[0]));
  init_var();

  if (isatty(0) == 1)
    res = parse_args(argc, argv);
  else
  {
    buff = calloc(512, sizeof (char));

    while ((c = read(STDIN_FILENO, buff, 512)) > 0)
      buff[c] = '\0';

    res = run_once(buff);
  }

  remove_all_var();

  return res;
}
