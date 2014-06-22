#include "free_long_struct.h"
#include "free_struct.h"
#include "free_rule.h"

void free_rule_for(s_rule_for *rule_for)
{
  if (NULL == rule_for)
    return;

  free(rule_for->name);
  for (size_t i = 0; i < rule_for->length_in; ++i)
    free(rule_for->in[i]);

  free(rule_for->in);
  free_struct_list(rule_for->group);
  free(rule_for);
}

void free_rule_while(s_rule_while *rule_while)
{
  if (NULL == rule_while)
    return;

  free_struct_and_or(rule_while->condition);
  free_struct_list(rule_while->group);
  free(rule_while);
}

void free_rule_until(s_rule_until *rule_until)
{
  if (NULL == rule_until)
      return;

  free_struct_list(rule_until->group);
  free_struct_and_or(rule_until->condition);
  free(rule_until);
}

void free_rule_if(s_rule_if *rule_if)
{
  if (NULL == rule_if)
    return;

  free_struct_and_or(rule_if->condition);
  free_struct_list(rule_if->action);
  free_struct_list(rule_if->elseif);
  free(rule_if);
}
