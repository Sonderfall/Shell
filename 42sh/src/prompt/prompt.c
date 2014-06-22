#define _BSD_SOURCE
#include "prompt.h"
#include "../substitution/var_sub.h"
#include <time.h>

static char *get_time(void)
{
  char      *res = NULL;
  char      *str_time;
  time_t    ltime;

  res = malloc(sizeof (char) * 12);
  time(&ltime);
  str_time = ctime(&ltime);
  strncpy(res, str_time, 10);
  res[11] = '\0';
  return res;
}

static char *get_special(char c)
{
  char *special = NULL;

  if (c == 'd')
    special = get_time();
  else if (c == 'D')
    special = "\\D";
  else if (c == 'e')
    special = getenv("USER");
  else if (c == 'h' || c == 'H')
    special = getenv("HOST");
  else if (c == 's')
    special = parse_variable("$0");
  else if (c == 'w')
    special = getenv("PWD");
  else if (c == 'W')
    special = basename("PWD");
  else if (c == 'n')
    special = "\n";

  return special;
}

static void shift_realloc(char **res, int *size)
{
  *size = (*size == 0) ? 1 : *size << 1;
  *res = realloc(*res, sizeof (char) * *size);
}

static char *set_string(char *string, const char *special, int *size, int *pos)
{
  int length;

  length = strlen(special);
  while (*pos + length > *size)
    shift_realloc(&string, size);
  strncpy(string + *pos, special, length);
  *pos += length + 1;

  return string;
}

char *set_prompt(const char *ps)
{
  char  *ps_var = NULL;
  char  *res = NULL;
  char  *special = NULL;
  int   pos_write = 0;
  int   size = 0;

  ps_var = (getenv(ps)) ? getenv(ps) : "\\w-\\d";
  for (int pos = 0; ps_var[pos] != '\0'; ++pos)
  {
    if (size == pos_write)
      shift_realloc(&res, &size);
    if (ps_var[pos] != '\\')
      res[pos_write++] = ps_var[pos];
    else
    {
      special = get_special(ps_var[++pos]);
      if (special == NULL)
        continue;
      res = set_string(res, special, &size, &pos_write);
      if (ps_var[pos] == 'd')
        free(special);
      --pos_write;
    }
  }
  res[pos_write] = '\0';

  return res;
}
