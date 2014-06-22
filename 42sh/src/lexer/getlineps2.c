#include "getlineps2.h"

int getline_ps2(char **cmd, int *index)
{
  if (((*cmd)[(*index)] == '\0') ||
      ((*cmd)[(*index)] == '\\' && (*cmd)[(*index) + 1 ] == '\0'))
  {
    free((*cmd));

    *cmd = readline("PS2");

    *index = -1;
    return 1;
  }

  return 0;
}
