#include "read_tree.h"

static char *read_redirect(s_redirection *redirect)
{
  char *root_node;
  char ionumber[64];
  char word[64];

  root_node = write_label("NOD_REDIRECT", redirect);

  ionumber[0] = redirect->ionumber + 48;
  ionumber[1] = '\0';
  strncpy(word, redirect->word, strlen(redirect->word));

  write_link(root_node, ionumber);
  write_link(root_node, word);

  return root_node;
}

static char *read_prefix(s_prefix *node_prefix)
{
  char *res;
  int  length;

  if (node_prefix->type == WORD)
  {
    length = strlen(node_prefix->prefix.word) + 1;
    res = malloc((length + 1) * sizeof (char));
    strncpy(res, node_prefix->prefix.word, length);

    return res;
  }
  else
  {
    return read_redirect(node_prefix->prefix.redirect);
  }
}

static char *read_element(s_element *node_element)
{
  char *res;
  int  length;

  if (node_element->type == WORD)
  {
    length = strlen(node_element->element.word) + 1;
    res = malloc((length + 1) * sizeof (char));
    strncpy(res, node_element->element.word, length);

    return res;
  }
  else
  {
    return read_redirect(node_element->element.redirect);
  }
}

static char *read_funcdec(s_funcdec *node_funcdec)
{
  char *root_node;
  char *r_sh_cmd;

  root_node = write_label(node_funcdec->name, node_funcdec);
  r_sh_cmd = read_shell_cmd(node_funcdec->cmd);
  write_link(root_node, r_sh_cmd);
  free(r_sh_cmd);

  return root_node;
}

char *read_shell_cmd(s_shell_cmd *node_sh_cmd)
{
  if (node_sh_cmd->type == LIST)
    return read_list(node_sh_cmd->cmd.list);
  else if (node_sh_cmd->type == RULE_FOR)
    return read_for(node_sh_cmd->cmd.rule_for);
  else if (node_sh_cmd->type == RULE_WHILE)
    return read_while(node_sh_cmd->cmd.rule_while);
  else if (node_sh_cmd->type == RULE_UNTIL)
    return read_until(node_sh_cmd->cmd.rule_until);
  else if (node_sh_cmd->type == RULE_CASE)
    return read_case(node_sh_cmd->cmd.rule_case);
  else
    return read_if(node_sh_cmd->cmd.rule_if);
}


static char *read_simple_cmd(s_simple_cmd *node_simp_cmd)
{
  size_t i_pref;
  size_t i_elem;
  char   *root_node;
  char   *r_value;

  root_node = write_label("NOD_SIMPLE_COMMAND", node_simp_cmd);

  for (i_pref = 0; i_pref < node_simp_cmd->length_prefix; i_pref++)
  {
    r_value = read_prefix(node_simp_cmd->prefix[i_pref]);
    write_link(root_node, r_value);
    free(r_value);
  }
  for (i_elem = 0; i_elem < node_simp_cmd->length_element; i_elem++)
  {
    r_value = read_element(node_simp_cmd->element[i_elem]);
    write_link(root_node, r_value);
    free(r_value);
  }

  return root_node;
}

static char *read_command(s_cmd *node_cmd)
{
  if (node_cmd->type == SIMPLE_COMMAND)
    return read_simple_cmd(node_cmd->cmd.simple_cmd);
  else if (node_cmd->type == SHELL_COMMAND)
    return read_shell_cmd(node_cmd->cmd.shell_cmd);
  else
    return read_funcdec(node_cmd->cmd.funcdec);
}

static char *read_pipeline(s_pipeline *node_pipeline)
{
  size_t i;
  char   **node_names;
  char   *root_node;
  char   *r_value;

  root_node = write_label("NOD_PIPELINE", node_pipeline);
  node_names = malloc(node_pipeline->length * (sizeof (char *)));
  for (i = 0; i < node_pipeline->length; i++)
  {
    node_names[i] = malloc(64 * sizeof (char));
    r_value = read_command(node_pipeline->commands[i]);
    strncpy(node_names[i], r_value, strlen(r_value));
    free(r_value);
  }

  for (i = 0; i < node_pipeline->length; i++)
    write_link(root_node, node_names[i]);

  for (i = 0; i < node_pipeline->length; i++)
    free(node_names[i]);
  free(node_names);

  return root_node;
}


char *read_and_or(s_and_or *node_and_or)
{
  char   *root_node;
  char   *r_value;

  root_node = write_label("NOD_AND_OR", node_and_or);

  r_value = read_pipeline(node_and_or->pipeline);
  write_link(root_node, r_value);
  free(r_value);

  if (node_and_or->connection != NONE)
  {
    r_value = read_and_or(node_and_or->next);
    write_link(root_node, r_value);
    free(r_value);
  }

  return root_node;
}

char *read_list(s_list *node_list)
{
  size_t i;
  char   **node_names;
  char   *root_node;
  char   *r_and_or;

  root_node = write_label("NOD_LIST", node_list);

  node_names = malloc(node_list->length * (sizeof (char *)));
  for (i = 0; i < node_list->length; i++)
  {
    node_names[i] = malloc(64 * (sizeof (char)));
    r_and_or = read_and_or(node_list->and_or[i]);
    strncpy(node_names[i], r_and_or, strlen(r_and_or));
    free(r_and_or);

    write_link(root_node, node_names[i]);
  }

  for (i = 0; i < node_list->length; i++)
    free(node_names[i]);
  free(node_names);

  return root_node;
}
