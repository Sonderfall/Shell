#define _BSD_SOURCE
#include "execution.h"

static void *output_redirection(s_redirection *redirection)
{
  int option;
  int fd;

  if (redirection->type == DOUBLE_CHEVRON_RIGHT)
    option = O_WRONLY | O_CREAT | O_APPEND;
  else
    option = O_WRONLY | O_CREAT;

  if ((fd = open(redirection->word, option, 0644)) == -1)
    return BAD_REDIRECTION;


  /* TODO add the fd to a global variable so we can close it later */
  /* TODO change the STDOUT_FILE to the fd of the realine */
  g_global.prev_fd = redirection->ionumber;
  g_global.cur_fd = fd;

  dup2(fd, redirection->ionumber);

  return NULL;
}

static void *input_redirection(s_redirection *redirection)
{
  char          *str = NULL;
  struct stat   info;
  int           fd;

  if (stat(redirection->word, &info) == -1)
    return BAD_REDIRECTION;

  str = malloc(sizeof (char) * (info.st_size + 1));
  fd = open(redirection->word, O_RDONLY);
  read(fd, str, info.st_size);
  close(fd);

  /* TODO verify that this is the correct way */
  write(STDIN_FILENO, str, info.st_size);

  return str;
}

static void *rw_redirection(s_redirection *redirection)
{
  char *s = NULL;

  s = input_redirection(redirection);

  if (s == BAD_REDIRECTION)
    return BAD_REDIRECTION;

  if (output_redirection(redirection) == BAD_REDIRECTION)
  {
    free(s);
    return BAD_REDIRECTION;
  }

  return s;
}

static void *here_document(s_redirection *redirection)
{
  setenv("IFS", redirection->word, 1);

  return NULL;
}

void *execute_redirection(s_redirection *redirection)
{
  if (NULL == redirection)
    return BAD_REDIRECTION;

  switch (redirection->type)
  {
    case SIMPLE_CHEVRON_RIGHT:
    case DOUBLE_CHEVRON_RIGHT:
    case CHEVRON_PIPE:
    case AMPERSAND_CHEVRON_RIGHT:
      return output_redirection(redirection);
    case SIMPLE_CHEVRON_LEFT:
    case AMPERSAND_CHEVRON_LEFT:
      return input_redirection(redirection);
    case CHEVRON_LEFT_RIGHT:
      return rw_redirection(redirection);
    case DOUBLE_CHEVRON_LEFT:
    case CHEVRON_HYPHEN:
      return here_document(redirection);
  }
  return BAD_REDIRECTION;
}
