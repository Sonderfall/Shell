#include "execution.h"

int execute_rule_while(s_rule_while *rule)
{
  int res = 0;

  while (res == 0 && execute_and_or(rule->condition) == 0)
    res = execute_list(rule->group);

  return res;
}

int execute_rule_until(s_rule_until *rule)
{
  int res = 0;

  do {
    res = execute_list(rule->group);
  } while (res == 0 && execute_and_or(rule->condition) == 1);

  return res;
}

int execute_rule_if(s_rule_if *rule)
{
  int res = 0;

  if (execute_and_or(rule->condition) == 0)
    execute_list(rule->action);
  else
    execute_list(rule->elseif);

  return res;
}

int execute_rule_for(s_rule_for *rule_for)
{
  int res = 0;

  for (size_t i = 0; i < rule_for->length_in && res == 0; i++)
    res = execute_list(rule_for->group);

  return res;
}
