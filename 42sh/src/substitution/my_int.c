#include "my_int.h"

int intlen(int i)
{
  int len = 0;

  while (i != 0)
  {
    i = i / 10;
    len++;
  }

  return len;
}

char *itoa(int i)
{
  char *str = NULL;
  int  j;
  int  len;

  len = intlen(i);

  if (i == 0)
  {
    str = malloc(2 * sizeof (char));
    strncpy(str, "0", 2);
    return str;
  }
  else
  {
    for (j = 0; i != 0; j++)
    {
      str = realloc(str, (65 + j) * sizeof (char));
      str[len - 1 - j] = i % 10 + '0';
      i = i / 10;
    }
    str[len] = '\0';
  }

  return str;
}
