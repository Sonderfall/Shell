#include "execution.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void free_pipes(size_t length, int **pipes)
{
  for (size_t i = 0; i < length; ++i)
  {
    close(pipes[i][0]);
    close(pipes[i][1]);
    free(pipes[i]);
  }
  free(pipes);
}

static void set_pipe(int **pipes, size_t pos, size_t max)
{
  if (pos != 0)
  {
    dup2(STDIN_FILENO, pipes[pos - 1][0]);
    close(pipes[pos - 1][1]);
  }
  close(pipes[pos][0]);
  if (pos != max - 1)
    dup2(pipes[pos][1], STDOUT_FILENO);
}

static int get_return_value(int     *tab_res,
                            int     *pids,
                            int     **pipes,
                            size_t  length)
{
  int res = 0;

  for (size_t i = 0; i < length; ++i)
    res |= WEXITSTATUS(tab_res[i]);
  free_pipes(length, pipes);
  free(tab_res);
  free(pids);

  return res;
}

static int exec_cmds(int           *pids,
                     int           **pipes,
                     int           *tab_res,
                     s_pipeline    *pipeline)
{
  for (size_t i = 0; i < pipeline->length; ++i)
  {
    pids[i] = fork();
    if (pids[i] == -1)
    {
      free_pipes(pipeline->length, pipes);
      free(tab_res);
      free(pids);
      return 1;
    }
    if (pids[i] == 0)
    {
      set_pipe(pipes, i, pipeline->length);
      execute_cmd(pipeline->commands[i]);
    }
  }
  return 0;
}

static int execute_pipe(s_pipeline *pipeline, int **pipes)
{
  int pos = 0;
  int *tab_res = NULL;
  int *pids = NULL;

  tab_res = malloc(sizeof (int) * pipeline->length);
  pids = malloc(sizeof (int) * pipeline->length);

  if (exec_cmds(pids, pipes, tab_res, pipeline) == 1)
    return 1;

  while (waitpid(-1, tab_res + pos, 0))
  {
    if (errno == ECHILD)
      break;
    ++pos;
  }

  return get_return_value(tab_res, pids, pipes, pipeline->length);
}

int execute_pipeline(s_pipeline *pipeline)
{
  int **pipes = NULL;

  if (pipeline->length == 1)
    return execute_cmd(pipeline->commands[0]);

  pipes = malloc(sizeof (int *) * pipeline->length);
  for (size_t i = 0; i < pipeline->length; ++i)
  {
    pipes[i] = malloc(sizeof (int) * 2);
    pipe(pipes[i]);
  }
  return execute_pipe(pipeline, pipes);
}
