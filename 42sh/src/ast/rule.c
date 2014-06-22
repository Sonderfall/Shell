#include "rule.h"
#include <string.h>

s_rule_while *create_rule_while(s_and_or *condition, s_list *group)
{
  s_rule_while *res = NULL;

  if (NULL == condition || NULL == group)
    return NULL;

  res = malloc(sizeof (s_rule_while));
  res->condition = condition;
  res->group = group;

  return res;
}

s_rule_if *create_rule_if(s_and_or *condition, s_list *action, s_list *elseif)
{
  s_rule_if *res = NULL;

  if (NULL == condition || NULL == action)
    return NULL;

  res = malloc(sizeof (s_rule_if));
  res->condition = condition;
  res->elseif = elseif;
  res->action = action;

  return res;
}

s_rule_for *create_rule_for(char *name, char **in, size_t argc, s_list *group)
{
  s_rule_for *res = NULL;
  int        size;

  if (NULL == name || NULL == in || NULL == group)
    return NULL;

  // Note: you can free name and in after creating the node

  res = malloc(sizeof (s_rule_for));
  size = strlen(name);
  res->name = malloc(sizeof (char) * (size + 1));
  strncpy(res->name, name, size);
  res->in = malloc(sizeof (char *) * argc);

  for (size_t i = 0; i < argc; ++i)
  {
    size = strlen(in[i]);
    res->in[i] = malloc((size + 1) * sizeof (char));
    strncpy(res->in[i], in[i], size);
  }

  res->group = group;

  return res;
}

s_rule_until *create_rule_until(s_list *group, s_and_or *condition)
{
  s_rule_until *res = NULL;

  if (NULL == group || NULL == condition)
    return NULL;

  res = malloc(sizeof (s_rule_until));
  res->group = group;
  res->condition = condition;

  return res;
}
