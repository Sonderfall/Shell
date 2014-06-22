#define _BSD_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../execution/execution.h"
#include "../builtins/builtins.h"

static char *read_file(char *path)
{
  int         fd;
  struct stat info;
  char        *buff = NULL;

  fd = open(path, O_RDONLY);

  if (fd == -1)
    return NULL;

  if (fstat(fd, &info) == -1)
  {
    close(fd);

    return NULL;
  }

  buff = malloc(sizeof (char) * (info.st_size + 1));

  if (read(fd, buff, info.st_size) == -1)
  {
    close(fd);
    free(buff);

    return NULL;
  }
  close(fd);

  return buff;
}

static int execute_command_list(s_list *list)
{
  int res = 1;

  res = execute_list(list);
  free_struct_list(list);

  return res;
}

static int free_content(char *content)
{
  free(content);
  return 1;
}

int builtin_source(s_simple_cmd *command)
{
  char      *content = NULL;
  s_tokens  *list = NULL;
  s_list    *ast = NULL;

  if (command->length_element < 2)
  {
    printf("42sh: source: filename argument required\n");
    return 1;
  }

  content = read_file(command->element[1]->element.word);

  if (content == NULL)
    return 1;

  list = lexer(content);

  if (list == NULL)
    free_content(content);

  ast = parse_list(&list);

  if (ast == NULL)
  {
    while (list != NULL)
      list = eat_token(list);
    free_content(content);
  }

  return execute_command_list(ast);
}
