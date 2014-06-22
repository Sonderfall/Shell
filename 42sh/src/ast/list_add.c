#include "list_add.h"

void list_add_element(s_list **list, s_and_or *element)
{
  if (element == NULL)
    return;

  if (*list == NULL)
  {
    *list = malloc(sizeof (s_list));
    (*list)->and_or = NULL;
    (*list)->length = 0;
  }

  (*list)->and_or = realloc((*list)->and_or, sizeof (s_and_or *) *
                         (++((*list)->length)));
  (*list)->and_or[(*list)->length - 1] = element;
}

void pipeline_add_element(s_pipeline **list, s_cmd *element)
{
  if (element == NULL)
    return;

  if (*list == NULL)
  {
    *list = malloc(sizeof (s_list));
    (*list)->commands = NULL;
    (*list)->length = 0;
  }

  (*list)->commands = realloc((*list)->commands, sizeof (s_and_or *) *
                           (++((*list)->length)));
  (*list)->commands[(*list)->length - 1] = element;
}

void simple_cmd_add_element(s_simple_cmd    **list,
                            s_prefix        *prefix,
                            s_element       *element)
{
  /* Check that only one if not null at the same time */
  if (!((NULL == element) ^ (NULL == prefix)))
    return;


  if (*list == NULL)
  {
    *list = malloc(sizeof (s_simple_cmd));
    (*list)->prefix = NULL;
    (*list)->length_prefix = 0;
    (*list)->element = NULL;
    (*list)->length_element = 0;
  }
  if (element)
  {
    (*list)->element = realloc((*list)->element, sizeof (s_element *) *
                            (++((*list)->length_element)));
    (*list)->element[(*list)->length_element - 1] = element;
  }
  if (prefix)
  {
    (*list)->prefix = realloc((*list)->prefix, sizeof (s_prefix *) *
                            (++((*list)->length_prefix)));
    (*list)->prefix[(*list)->length_prefix - 1] = prefix;
  }
}
