#include "free_struct.h"
#include "union.h"
#include "free_long_struct.h"

void free_struct_list(s_list *list)
{
  if (list == NULL)
    return;

  for (size_t i = 0; i < list->length; ++i)
    free_struct_and_or(list->and_or[i]);

  free(list->and_or);
  free(list);
}

void free_struct_pipeline(s_pipeline *pipeline)
{

  if (pipeline == NULL)
    return;

  for (size_t i = 0; i < pipeline->length; ++i)
    free_struct_cmd(pipeline->commands[i]);

  free(pipeline->commands);
  free(pipeline);
}

void free_struct_simple_cmd(s_simple_cmd *cmd)
{
  if (NULL == cmd)
    return;

  for (size_t i = 0; i < cmd->length_prefix; ++i)
    free_prefix(cmd->prefix[i]);

  free(cmd->prefix);

  for (size_t i = 0; i < cmd->length_element; ++i)
    free_element(cmd->element[i]);

  free(cmd->element);
  free(cmd);
}
