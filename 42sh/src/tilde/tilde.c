#include "tilde.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static char *get_tilde_history()
{
  char *res = NULL;
  char *tmp;
  int  length;

  tmp = (getenv("OLDPWD")) ? getenv("OLDPWD") : getenv("HOME");
  length = strlen(tmp) + 1;
  res = malloc(sizeof (char) * length);
  strncpy(res, tmp, length);
  return res;
}

char *parse_tilde(char *tilde)
{
  char *res = NULL;
  int length;

  if (!strcmp(tilde, "~"))
  {
    length = strlen(getenv("HOME")) + 1;
    res = malloc(sizeof (char) * length);
    strncpy(res, getenv("HOME"), length);
    return res;
  }
  else if (!strcmp(tilde, "~-"))
    get_tilde_history();
  else if (strchr(tilde, '~') == tilde)
  {
    length = strlen(tilde + 1) + 1;
    res = malloc(sizeof (char) * (length + 6));
    sprintf(res, "/home/%s", tilde + 1);
  }

  return res;
}
