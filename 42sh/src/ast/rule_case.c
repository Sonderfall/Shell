#include "free_long_struct.h"
#include "rule_case.h"
#include <string.h>

void add_rule_case(s_rule_case  *rule_case,
                   s_case_item  *item,
                   char         *name)
{
  int length;

  if (NULL == item)
    return;

  if (NULL == rule_case)
  {
    if (NULL == name)
      return;
    rule_case = malloc(sizeof (s_rule_case));

    length = strlen(name);
    rule_case->name = malloc(sizeof (char) * (length + 1));
    strncpy(rule_case->name, name, length);

    rule_case->items = NULL;
  }

  rule_case->items = realloc(rule_case->items, sizeof (s_rule_case *) *
                             ++rule_case->length);
  rule_case->items[length - 1] = item;
}

s_case_item *create_rule_case(char *value, s_list *group)
{
  s_case_item *res = NULL;
  int         length = 0;

  if (group == NULL || value == NULL)
    return NULL;

  res = malloc(sizeof (s_case_item));
  length = strlen(value);
  res->value = malloc(sizeof (char) * (length + 1));
  strncpy(res->value, value, length);
  res->group = group;

  return res;
}

void free_rule_case(s_rule_case *rule_case)
{
  if (NULL == rule_case)
    return;

  free(rule_case->name);

  for (size_t i = 0; i < rule_case->length; ++i)
    free_rule_case_item(rule_case->items[i]);

  free(rule_case->items);
  free(rule_case);
}

void free_rule_case_item(s_case_item *case_item)
{
  if (NULL == case_item)
    return;

  free(case_item->value);
  free_struct_list(case_item->group);
  free(case_item);
}
