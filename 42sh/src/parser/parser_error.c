#include "parser.h"
#include <stdio.h>

void *parse_error(s_tokens *token)
{
  if (token == NULL)
    return NULL;

  printf("Parser Error: %s\n", token->token);
  while (token != NULL)
    token = eat_token(token);

  return NULL;
}
