#define _BSD_SOURCE
#include "var_sub.h"

void init_var(void)
{
  int  i;
  char *str;

  i = getpid();
  str = itoa(i);
  add_var("$", str);
  free(str);

  i = random() % 32768;
  str = itoa(i);
  add_var("RANDOM", str);
  add_var("?", "0");

  free(str);
}
