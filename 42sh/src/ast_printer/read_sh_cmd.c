#include "read_sh_cmd.h"
#include <stdio.h>

char *read_for(s_rule_for *node_for)
{
  char   *root_node;
  char   name[64] = "RULE_FOR_";
  char   *r_value;
  size_t i;

  strcat(name, node_for->name);
  root_node = write_label(name, node_for);

  for (i = 0; i < node_for->length_in; i++)
  {
    r_value = write_label(node_for->in[i], node_for);
    write_link(root_node, r_value);
    free(r_value);
  }

  r_value = read_list(node_for->group);
  write_link(root_node, r_value);
  free(r_value);

  return root_node;
}

char *read_while(s_rule_while *node_while)
{
  char *root_node;
  char *r_value;

  root_node = write_label("RULE_WHILE", node_while);

  r_value = read_and_or(node_while->condition);
  write_link(root_node, r_value);
  free(r_value);

  r_value = read_list(node_while->group);
  write_link(root_node, r_value);
  free(r_value);

  return root_node;
}


char *read_until(s_rule_until *node_until)
{
  char *root_node;
  char *r_value;

  root_node = write_label("RULE_UNTIL", node_until);

  r_value = read_and_or(node_until->condition);
  write_link(root_node, r_value);
  free(r_value);

  r_value = read_list(node_until->group);
  write_link(root_node, r_value);
  free(r_value);

  return root_node;
}

static char *read_case_item(s_case_item *item)
{
  char *root_node;
  char *r_value;

  root_node = write_label(item->value, item);

  r_value = read_list(item->group);
  write_link(root_node, r_value);
  free(r_value);

  return root_node;
}

char *read_case(s_rule_case *node_case)
{
  char   *root_node;
  char   *r_value;
  char   name[64] = "RULE_CASE_";
  size_t i;

  strcat(name, node_case->name);

  root_node = write_label(name, node_case);

  for (i = 0; i < node_case->length; i++)
  {
    r_value = read_case_item(node_case->items[i]);
    write_link(root_node, r_value);
    free(r_value);
  }

  return root_node;
}

char *read_if(s_rule_if *node_if)
{
  char *root_node;
  char *r_value;

  root_node = write_label("RULE_IF", node_if);

  r_value = read_and_or(node_if->condition);
  write_link(root_node, r_value);
  free(r_value);

  r_value = read_list(node_if->action);
  write_link(root_node, r_value);
  free(r_value);

  if (node_if->elseif != NULL)
  {
    r_value = read_list(node_if->elseif);
    write_link(root_node, r_value);
    free(r_value);
  }
  return root_node;
}

