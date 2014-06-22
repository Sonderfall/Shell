#define _BSD_SOURCE
#include "var_sub.h"

static void create_node(char *name, char *value)
{
  s_local_var *res = NULL;
  int         length;

  res = malloc(sizeof (s_local_var));

  length = strlen(name) + 1;
  res->name = malloc(sizeof (char) * length);
  strncpy(res->name, name, length);

  length = strlen(value) + 1;
  res->var = malloc(sizeof (char) * length);
  strncpy(res->var, value, length);

  res->next = g_global.local_vars;
  g_global.local_vars = res;
}

void add_var(char *name, char *var)
{
  s_local_var *ptr;
  int         length;

  ptr = g_global.local_vars;

  for (; ptr != NULL; ptr = ptr->next)
    if (strcmp(ptr->name, name) == 0)
    {
      free(ptr->name);
      free(ptr->var);
      break;
    }

  if (ptr == NULL)
    create_node(name, var);
  else
  {
    length = strlen(name) + 1;
    ptr->name = malloc(sizeof (char) * length);
    strncpy(ptr->name, name, length);

    length = strlen(var) + 1;
    ptr->var = malloc(sizeof (char) * length);
    strncpy(ptr->var, var, length);
  }
}

void remove_var(char *name)
{
  s_local_var *cur;
  s_local_var *prev;

  cur = g_global.local_vars;

  while (cur != NULL)
  {
    if (strcmp(cur->name, name) == 0)
    {
      if (prev == NULL)
	g_global.local_vars = cur->next;
      else
	prev->next = cur->next;

      free(cur->name);
      if (cur->var != NULL)
	free(cur->var);
      free(cur);

      break;
    }

    prev = cur;
    cur = cur->next;
  }
}

void remove_all_var(void)
{
  s_local_var *ptr;

  ptr = g_global.local_vars;

  while (ptr != NULL)
  {
    g_global.local_vars = ptr->next;

    free(ptr->name);
    if (ptr->var != NULL)
      free(ptr->var);
    free(ptr);

    ptr = g_global.local_vars;
  }
}

static void random_case(s_local_var *ptr)
{
  int  rand_i;
  char *str;

  srandom(atoi(ptr->var));
  rand_i = random() % 32768;
  str = itoa(rand_i);
  free(ptr->var);
  ptr->var = str;

}

static char *get_var(char *parameter, char *ope, char *word)
{
  s_local_var *ptr;
  char        *str = NULL;

  ptr = g_global.local_vars;

  if (parameter != NULL && (str = getenv(parameter)) != NULL)
    return str;

  for (; ptr != NULL && str == NULL && parameter != NULL; ptr = ptr->next)
    if (strcmp(ptr->name, parameter) == 0)
    {
      if (strcmp(parameter, "RANDOM") == 0)
	random_case(ptr);
      str = ptr->var;
    }

  if (!ope || (str &&
	       (!strcmp(ope, ":-") || !strcmp(ope, "-") || !strcmp(ope, ":=") ||
		!strcmp(ope, "=") || !strcmp(ope, ":?") || !strcmp(ope, "?"))))
    return str;
  else if (!strcmp(ope, ":=") || !strcmp(ope, "="))
  {
    add_var(parameter, word);
    return get_var(parameter, NULL, NULL);
  }
  else if ((str != NULL && (!strcmp(ope, ":+") || !strcmp(ope, "+"))) ||
	   (!strcmp(ope, ":-") || !strcmp(ope, "-")))
    return word;
  return NULL;
}

static void parse_op_word(char *cmd, int *index, char **ope, char **word)
{
  int j = 0;

  (*ope) = malloc(8 * sizeof (char));
  (*ope)[j] = cmd[(*index)];
  if (cmd[(*index)] == ':')
    if (cmd[(*index) + 1] != '-' && cmd[(*index) + 1] != '=' &&
	cmd[(*index) + 1] != '?' && cmd[(*index) + 1] != '+')
    {
      (*index)++;
      (*ope)[(++j)] = cmd[(*index)];
    }
  (*ope)[(++j)] = '\0';

  for (j = 0, (*index) = (*index) + 1;
       cmd[(*index)] != '}' && cmd[(*index)] != '\0';
       (*index)++, j++)
  {
    if (j % 64 == 0)
      (*word) = realloc((*word), (65 + j) * sizeof (char));
    (*word)[j] = cmd[(*index)];
  }
  (*word)[j] = '\0';
}

static char *get_copy_and_free(char *parameter, char *ope, char *word)
{
  char *var = NULL;
  char *ret_value = NULL;
  int  i;

  var = get_var(parameter, ope, word);

  if (var != NULL)
  {
    for (i = 0; var[i] != '\0'; i++)
    {
      if (i % 64 == 0)
	ret_value = realloc(ret_value, (65 + i) * sizeof (char));

      ret_value[i] = var[i];
    }
    ret_value[i] = '\0';
  }

  if (parameter != NULL)
    free(parameter);
  if (ope != NULL)
    free(ope);
  if (word != NULL)
    free(word);

  return ret_value;
}

static char *get_parameter(char *cmd, int *index, char end_of_var)
{
  int  j;
  char *parameter = NULL;

  for (j = 0;
       cmd[(*index)] != end_of_var && cmd[(*index)] != '\0';
       (*index)++, j++)
  {
    if (j % 64 == 0)
      parameter = realloc(parameter, (65 + j) * sizeof (char));
    if ((cmd[(*index)] == '?' && j == 0) ||
	(cmd[(*index)] != '?' && cmd[(*index)] != '-' &&
	 cmd[(*index)] != '=' && cmd[(*index)] != ':' &&
	 cmd[(*index)] != '+'))
      parameter[j] = cmd[(*index)];
    else
      break;
  }
  if (parameter != NULL)
    parameter[j] = '\0';

  return parameter;
}

char *parse_variable(char *cmd)
{
  char end_of_var = ' ';
  char *parameter = NULL;
  char *ope = NULL;
  char *word = NULL;
  char *var = NULL;
  int  index = 1;

  if (cmd[index] == '{')
  {
    end_of_var = '}';
    index++;
  }

  parameter = get_parameter(cmd, &index, end_of_var);

  if (cmd[index] != '\0' && cmd[index] != end_of_var)
    parse_op_word(cmd, &index, &ope, &word);


  var = get_copy_and_free(parameter, ope, word);

  return var;
}

