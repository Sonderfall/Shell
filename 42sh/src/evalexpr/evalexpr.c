#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evalexpr.h"

static void error(const char *string, int pos)
{
  fprintf(stderr, "Unexepecte character '%c' at the position %d\n",
         string[pos], pos);
  fprintf(stderr, "%s\n", string);
  for (int i = 0; i < pos; ++i)
    fprintf(stderr, " ");
  fprintf(stderr, "^\n");
}

static char eat_operator(const char *string, char c, int *pos)
{
  if (string[*pos] != c)
    error(string, *pos);
  ++(*pos);
  return c;
}

static int eat_variable(const char *string, int *pos)
{
  char *value = NULL;
  char *name = NULL;
  char length = 0;
  int  res = 0;

  if (!isalnum(string[*pos]))
    error(string, *pos);

  while (isalnum(string[*pos + length]))
    ++length;

  name = malloc(sizeof (char) * (length + 1));
  strncpy(name, string + *pos, length);
  name[length] = '\0';
  value = get_variable_value(g_variable, name);
  free(name);
  if (isdigit(value[0]))
    res = atoi(value);
  *pos += length;

  return res;
}

static int eat_int(const char *string, int *pos)
{
  int res;

  if (!isdigit(string[*pos]))
    error(string, *pos);
  res = atoi(string + 1);
  while (isdigit(string[*pos]))
    ++(*pos);

  return res;
}

s_ast *create_expression(const char *string)
{
  s_ast *res = NULL;
  int pos = 0;


  return res;
}
