#include "free_struct.h"
#include "union.h"
#include <string.h>

s_prefix *create_prefix(u_uprefix prefix, e_type_element type)
{
  s_prefix *res = NULL;
  int      length = 0;

  if (prefix.word == NULL)
    return NULL;

  res = malloc(sizeof (s_prefix));
  res->type = type;

  if (WORD == type)
  {
    length = strlen(prefix.word);
    res->prefix.word = malloc(sizeof (char) * (length + 1));
    strncpy(res->prefix.word, prefix.word, length + 1);
  }

  if (REDIRECTION == type)
    res->prefix.redirect = prefix.redirect;

  return res;
}

void free_prefix(s_prefix *prefix)
{
  if (NULL == prefix)
    return;

  if (WORD == prefix->type)
    free(prefix->prefix.word);

  if (REDIRECTION == prefix->type)
    free_struct_redirection(prefix->prefix.redirect);

  free(prefix);
}

s_element *create_element(u_uelement element, e_type_element type)
{
  s_element *res = NULL;
  int       length = 0;

  if (element.word == NULL)
    return NULL;

  res = malloc(sizeof (s_element));
  res->type = type;

  if (WORD == type)
  {
    length = strlen(element.word);
    res->element.word = malloc(sizeof (char) * (length + 1));
    strncpy(res->element.word, element.word, length + 1);
  }

  if (REDIRECTION == type)
    res->element.redirect = element.redirect;

  return res;
}

void free_element(s_element *element)
{
  if (NULL == element)
    return;

  if (WORD == element->type)
    free(element->element.word);

  if (REDIRECTION == element->type)
    free_struct_redirection(element->element.redirect);

  free(element);
}
