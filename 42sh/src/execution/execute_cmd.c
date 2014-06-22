#include "execution.h"

int execute_shell_command(s_shell_cmd *cmd)
{
  if (NULL == cmd)
    return 1;

  switch (cmd->type)
  {
    case LIST:
      return execute_list(cmd->cmd.list);
    case RULE_FOR:
      return execute_rule_for(cmd->cmd.rule_for);
    case RULE_WHILE:
      return execute_rule_while(cmd->cmd.rule_while);
    case RULE_UNTIL:
      return execute_rule_until(cmd->cmd.rule_until);
    case RULE_CASE:
      return execute_rule_case(cmd->cmd.rule_case);
    case RULE_IF:
      return execute_rule_if(cmd->cmd.rule_if);
  }
  return 1;
}

int execute_funcdec(s_funcdec *cmd)
{
  if (NULL == cmd)
    return 1;

  for (size_t i = 0; i < cmd->argc; i++)
    /* TODO add variable to gobal variable */
    cmd->argv[i] = cmd->argv[i];
  return execute_shell_command(cmd->cmd);

  for (size_t i = 0; i < cmd->argc; i++)
    /* TODO remove variable to gobal variable */
    cmd->argv[i] = cmd->argv[i];
}

static int exec_fork_cmd(char **s)
{
  int   status = 0;
  pid_t pid;

  pid = fork();

  if (pid == -1)
  {
    printf("failed to fork");
    exit(EXIT_FAILURE);
  }
  else if (pid == 0)
  {
    status = execvp(s[0], s);
    perror("Failed to execute command");
    exit(status);
  }

  g_global.cur_pid = pid;
  waitpid(pid, &status, 0);
  free(s);
  g_global.cur_pid = -1;
  dup2(STDOUT_FILENO, g_global.cur_fd);

  return WEXITSTATUS(status);
}

static void assign_variable(char *word)
{
  char *ptr = NULL;

  ptr = strchr(word, '=');
  if (ptr == NULL)
    return;

  ptr[0] = '\0';
  add_var(word, ptr + 1);
  ptr[0] = '=';
}

static char *check_variable(char **word)
{
  char *value;

  if ((*word) == NULL)
    return NULL;
  if ((*word)[0] == '$' && strlen(*word) > 1)
  {
    value = parse_variable((*word));
    free(*word);
    (*word) = value;
    return *word;
  }
  else if (strchr(*word, '~') == *word)
  {
    value = parse_tilde(*word);
    free(*word);
    *word = value;
    return *word;
  }
  else
    return *word;
}

int execute_simple_cmd(s_simple_cmd *cmd)
{
  char  **s = NULL;
  int   return_value;

  if (cmd == NULL)
    return 1;

  s = malloc(sizeof (char*) * (cmd->length_prefix + cmd->length_element + 1));

  for (size_t i = 0; i < cmd->length_prefix; ++i)
    if (cmd->prefix[i]->type == WORD)
      assign_variable(cmd->prefix[i]->prefix.word);
    else
      execute_redirection(cmd->prefix[i]->prefix.redirect);

  for (size_t i = 0; i < cmd->length_element; ++i)
    if (cmd->element[i]->type == WORD)
      s[i] = check_variable(&(cmd->element[i]->element.word));
    else
      execute_redirection(cmd->element[i]->element.redirect);

  return_value = is_builtins(cmd);
  if (return_value != -1)
  {
    free(s);
    return return_value;
  }

  s[cmd->length_prefix + cmd->length_element] = NULL;

  return_value = exec_fork_cmd(s);

  return return_value;
}

int execute_cmd(s_cmd *cmd)
{
  if (NULL == cmd)
    return 1;

  switch (cmd->type)
  {
    case SHELL_COMMAND:
      return execute_shell_command(cmd->cmd.shell_cmd);
    case SIMPLE_COMMAND:
      return execute_simple_cmd(cmd->cmd.simple_cmd);
    case FUNCDEC:
      return execute_funcdec(cmd->cmd.funcdec);
    case NO_TYPE:
      return 1;
  }

  return 0;
}
