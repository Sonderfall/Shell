#include "list_token.h"
#include <stdio.h>
#include <string.h>

s_tokens *token_add(char *token, e_type_token type, s_tokens *list)
{
  s_tokens *new = NULL;

  if (token[0] == '\0')
    return list;

  new = malloc(sizeof (s_tokens));
  new->token = token;
  new->type = type;
  new->next = NULL;
  new->tail = new;

  if (list == NULL)
    return new;
  else
  {
    list->tail->next = new;
    list->tail = new;
    return list;
  }
}

s_tokens *get_next_line(s_tokens *list)
{
  while (list && !strcmp(list->token, "\n"))
    list = eat_token(list);

  return list;
}

s_tokens *eat_token(s_tokens *list)
{
  s_tokens *ptr;

  if (list != NULL)
  {
    ptr = list->next;

    if (ptr != NULL)
      ptr->tail = list->tail;

    free(list->token);
    free(list);
    return ptr;
  }
  else
    return NULL;
}
