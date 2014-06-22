#include "variable.h"
#include <string.h>
#include <stdlib.h>

static s_variable *create_node(char *name, char *value)
{
  s_variable *res = NULL;
  int length;

  res = malloc(sizeof (s_variable));

  length = strlen(name) + 1;
  res->name = malloc(sizeof (char) * length);
  strncpy(res->name, name, length);

  length = strlen(value) + 1;
  res->value = malloc(sizeof (char) * length);
  strncpy(res->value, value, length);

  res->next = NULL;
  res->prev = NULL;

  return res;
}

static void free_node(s_variable *node)
{
  free(node->name);
  free(node->value);
}

void add_variable(s_variable **list, char *name, char *value)
{
  s_variable *top = NULL;

  top = create_node(name, value);
  top->next = *list;
  (*list)->prev = top;

  *list = top;
}

void remove_variable(s_variable **list, char *name)
{
  s_variable *tmp = *list;

  if (!*list)
    return;

  if (!strcmp(name, tmp->name))
  {
    *list = (*list)->next;
    (*list)->prev = NULL;
    free(tmp);
    return;
  }
  while (tmp && strcmp(tmp->name, name))
    tmp = tmp->next;

  if (!tmp)
    return;

  tmp->prev = tmp->next;
  free(tmp);
}

void remove_all_variable(s_variable **list)
{
  s_variable *tmp = NULL;

  while (*list)
  {
    tmp = *list;
    *list = (*list)->next;
    free(tmp);
  }
  *list = NULL;
}

char *get_variable_value(s_variable *list, char *name)
{
  s_variable *tmp = list;

  while (tmp && strcmp(tmp->name, name))
    tmp = tmp->next;

  return (tmp) ? tmp->value : NULL;
}
