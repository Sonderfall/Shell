#include "alias.h"


static void create_node(char *name, char *value)
{
  s_aliases *res = NULL;
  int       length;

  res = malloc(sizeof (s_aliases));

  length = strlen(name) + 1;
  res->name = malloc(length * sizeof (char));
  strncpy(res->name, name, length);

  length = strlen(value) + 1;
  res->value = malloc(length * sizeof (char));
  strncpy(res->value, value, length);

  res->next = g_global.aliases;
  g_aliases = res;
}

void add_alias(char *name, char *value)
{
  s_aliases *ptr;
  int       length;

  ptr = g_global.aliases;

  for (; ptr != NULL; ptr = ptr->next)
    if (strcmp(ptr->name, name) == 0)
    {
      free(ptr->value);
      break;
    }

  if (ptr == NULL)
    create_node(name, value);
  else
  {
    length = strlen(value) + 1;
    ptr->value = malloc(length * sizeof (char));
    strncpy(ptr->value, value, length);
  }
}

void unalias(char *name)
{
  s_aliases *cur;
  s_aliases *prev;

  cur = g_global.aliases;

  while (cur != NULL)
  {
    if (strcmp(cur->name, name) == 0)
    {
      if (prev == NULL)
	g_aliases = cur->next;
      else
	prev->next = cur->next;

      free(cur->name);
      if (cur->value != NULL)
	free(cur->value);
      free(cur);

      break;
    }

    prev = cur;
    cur = cur->next;
  }
}

void destroy_aliases(void)
{
  s_aliases *ptr;

  ptr = g_global.aliases;

  while (ptr != NULL)
  {
    g_global.aliases = ptr->next;

    free(ptr->name);
    if (ptr->value != NULL)
      free(ptr->value);
    free(ptr);

    ptr = g_global.aliases;
  }
}


/* Put the alias of name in buff, return 1 if found, 0 otherwise */
static int find_alias(char *name, char *buff)
{
  s_aliases *ptr;
  int       length;

  ptr = g_global.aliases;

  for (; ptr != NULL; ptr = ptr->next)
  {
    if (strcmp(ptr->name, name) == 0)
    {
      length = strlen(ptr->value) + 1;
      buff = malloc(length * sizeof (char));
      strncpy(buff, ptr->value, length);
      return 1;
    }
  }

  return 0;
}

char *get_alias(char *name)
{
  char *res;
  char *buff = NULL;
  int  found;
  int  length;

  length = strlen(name) + 1;
  res = malloc(length * sizeof (char));
  strncpy(res, name, length);

  while (1)
  {
    found = find_alias(res, buff);
    if (found)
    {
      free(res);
      res = buff;
      buff = NULL;

      if (strcmp(res, name) == 0)
	break;
    }
    else
      break;
  }

  return res;
}
