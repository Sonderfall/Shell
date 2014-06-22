#include "execution.h"

int execute_list(s_list *list)
{
  int res = 1;

  if (list == NULL)
    return 1;

  for (size_t i = 0; i < list->length; i++)
    res = execute_and_or(list->and_or[i]);

  return res;
}

int execute_and_or(s_and_or *and_or)
{
  int res = 1;

  if (and_or == NULL)
    return 1;

  res = execute_pipeline(and_or->pipeline);

  if (and_or->next != NULL)
  {
    if (and_or->connection == AND && res == 0)
      res = execute_and_or(and_or->next);

    else if (and_or->connection == OR && res == 1)
      res = execute_and_or(and_or->next);
  }
  return res;
}
