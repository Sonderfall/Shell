#include "ast_printer.h"

static FILE *file;

static char *add_tag(char *str, void *tag)
{
  char   c;
  char   *str_tag = tag;
  char   *concat_str;
  size_t len;
  size_t i;

  len = strlen(str);
  concat_str = malloc(65 * sizeof (char));

  for (i = 0; i < sizeof (size_t); i++)
  {
    if ((i + len) % 64 == 0)
      concat_str = realloc(concat_str, ((i + len) + 65) * sizeof (char));

    c = (str_tag[i] % 26) + 65;
    if (c < 65)
      c += 26;
    concat_str[len + i] = c;
  }
  strncpy(concat_str, str, strlen(str));
  concat_str[len + i] = '\0';

  return concat_str;
}

char *write_label(char *label, void *tag)
{
  char *name;

  name = add_tag(label, tag);

  fwrite("\"", sizeof (char), 1, file);
  fwrite(name, sizeof (char), strlen(name), file);
  fwrite("\"", sizeof (char), 1, file);
  fwrite(" [label=\"", sizeof (char), 9, file);
  fwrite(label, sizeof (char), strlen(label), file);
  fwrite("\"];\n", sizeof (char), 4, file);

  return name;
}

/*
** Write the link a -> b in the file
*/
void write_link(char *a, char *b)
{
  fwrite("\"", sizeof (char), 1, file);
  fwrite(a, sizeof (char), strlen(a), file);
  fwrite("\"", sizeof (char), 1, file);
  fwrite("->", sizeof (char), 2, file);
  fwrite("\"", sizeof (char), 1, file);
  fwrite(b, sizeof (char), strlen(b), file);
  fwrite("\"", sizeof (char), 1, file);
  fwrite(";\n", sizeof (char), 2, file);
}

void create_ast_dot(s_list *node_list)
{
  char *head_ast;

  file = fopen("ast.dot", "w");
  fwrite("digraph ast {\n", sizeof (char), 14, file);

  head_ast = read_list(node_list);
  free(head_ast);

  fwrite("}\n", sizeof (char), 2, file);
  fclose(file);
}
