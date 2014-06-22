#include "dquote_sub.h"

static char *sub_arithmetic(char *dquote_str, int *index)
{
  char *str = NULL;
  int  c_braces_count = 0;
  int  i;

  for (i = 0; c_braces_count != 2; i++, (*index)++)
  {
    if (i % 64 == 0)
      str = realloc(str, (i + 65) * sizeof (char));

    // If reach end before double )
    if (getline_ps2(&dquote_str, index))
      continue;

    if (dquote_str[(*index)] == '\\' && dquote_str[(*index)] == ')')
      c_braces_count--;

    str[i] = dquote_str[(*index)];

    if (dquote_str[(*index)] == ')')
      c_braces_count++;
  }
  str[i] = '\0';

  return str;
}

static char *sub_variable(char *dquote_str, int *index)
{
  char end_of_var = ' ';
  char *str = NULL;
  int  i;

  if (dquote_str[(*index) + 1] == '{')
    end_of_var = '}';

  for (i = 0; ; i++, (*index)++)
  {
    if (i % 64 == 0)
      str = realloc(str, (i + 65) * sizeof (char));

    if (end_of_var == ' ' &&
	(dquote_str[(*index)] == '\0' || dquote_str[(*index)] == ' ' ||
	 dquote_str[(*index)] == ':' || dquote_str[(*index)] == '-' ||
	 dquote_str[(*index)] == '+' || dquote_str[(*index)] == '=' ||
	 dquote_str[(*index)] == '?'))
	break;

    // If reach end before }
    if (getline_ps2(&dquote_str, index))
      continue;

    str[i] = dquote_str[(*index)];

    if (dquote_str[(*index)] == end_of_var)
      break;
  }

  (end_of_var == ' ') ? str[i] = '\0' : (str[i + 1] = '\0');

  return str;
}

static char *my_strcat(char *src, char *dst, int *index)
{

  for (int i = 0; src[i] != '\0'; i++, (*index)++)
  {
    if ((*index) % 64)
      dst = realloc(dst, (65 + (*index)) * sizeof (char));

    dst[(*index)] = src[i];
  }

  return dst;
}

static char *sub_dollar(char *dquote_str, int *index, char *str, int *index_str)
{
  char *strtoeval = NULL;
  char *strtocat = NULL;

  if (dquote_str[(*index) + 1] == ' ' || dquote_str[(*index) + 1] == '\n')
    str[(*index_str)] = '$';
  else if (dquote_str[(*index) + 1] == '(')
    if (dquote_str[(*index) + 2] == '(')
    {
      strtocat = sub_arithmetic(dquote_str, index);
      // TODO : Call arithmetic eval
      str = my_strcat(strtocat, str, index_str);
    }
    else
      // BONUS : call Command substitution
      for (; dquote_str[(*index)] == ')'; (*index)++)
	;
  else
  {
    strtoeval = sub_variable(dquote_str, index);
    strtocat = parse_variable(strtoeval);
    str = my_strcat(strtocat, str, index_str);
  }

  if (strtoeval != NULL)
    free(strtoeval);
  if (strtocat != NULL)
    free(strtocat);

  return str;
}


static char sub_backslash(char *dquote_str, int *index)
{
  char c;

  c = dquote_str[(*index) + 1];
  if (c == '$' || c == '`' || c == '"' || c == '\\' || c == '\n')
  {
    (*index)++;
    return c;
  }
  else
  {
    return '\\';
  }
}


char *sub_double_quote(char *dquote_str)
{
  char *str = NULL;
  int  i;
  int  j;

  for (j = 0, i = 0; dquote_str[i] != '\0'; i++, j++)
  {
    if (j % 64 == 0)
      str = realloc(str, (65 + j) * sizeof (char));

    if (dquote_str[i] == '\\')
    {
      str[j] = sub_backslash(dquote_str, &i);
      continue;
    }

    if (dquote_str[i] == '$')
    {
      str = sub_dollar(dquote_str, &i, str, &j);
      j--;
      i--;
      continue;
    }

    str[j] = dquote_str[i];
  }

  str[j] = '\0';

  return str;
}
