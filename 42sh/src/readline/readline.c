#include "readline.h"

static int read_user_input(char *buff, char *buff2, int *i);

static void escape(char *buff, char *buff2, int *i);

static void escape_arrow(char *buff, char *buff2, int *i);

static void ctrl_arrow(char *buff, char buff2, int *i);

static void ctrl_shortcut_ADE(char *buff, char buff2, int *i);

static void ctrl_shortcut_KL(char *buff, char buff2, int *i);

static void ctrl_shortcut(char *buff, char buff2, int *i);

static void backspace(char *buff, int *i);

static void write_char(char *buff, char *buff2, int *i);


static int read_user_input(char *buff, char *buff2, int *i)
{
  if (buff2[0] == 2 || buff2[0] == 6 || buff2[0] == 14 || buff2[0] == 16)
    ctrl_arrow(buff, buff2[0], i);

  else if (buff2[0] == 1 || buff2[0] == 4 || buff2[0] == 5 ||
           buff2[0] == 11 || buff2[0] == 12)
    ctrl_shortcut(buff, buff2[0], i);

  else if (buff2[0] == 27)
    escape(buff, buff2, i);

  else if (buff2[0] == 127)
  {
    if (*i)
      backspace(buff, i);
    --(*i);
  }

  else if (buff2[0] == 9)
    --(*i);

  else if (buff2[0] == 10)
    ;

  else
    write_char(buff, buff2, i);

  return buff2[0] == 10;
}

static void escape(char *buff, char *buff2, int *i)
{
  read(STDIN_FILENO, buff2, 1);

  if (buff2[0] == 91)
  {
    read(STDIN_FILENO, buff2, 1);

    if (buff2[0] == 51)
    {
      read(STDIN_FILENO, buff2, 1);

      if (buff2[0] == 126)
      {
        tputs(tgetstr("dc", NULL), 1, my_putchar);
        memmove(buff + *i, buff + *i + 1, strlen(buff) - *i + 1);
      }

      --(*i);
    }

    if (buff2[0] == 65 || buff2[0] == 66)
      --(*i);

    escape_arrow(buff, buff2, i);
  }

  else if (buff2[0] == 27)
    escape(buff, buff2, i);

  else
    read_user_input(buff, buff2, i);
}

static void escape_arrow(char *buff, char *buff2, int *i)
{
  size_t tmp = *i;

  if (buff2[0] == 67)
    tmp < strlen(buff) ? tputs(tgetstr("nd", NULL), 1, my_putchar) : --(*i);

  if (buff2[0] == 68)
  {
    if (*i > 0)
    {
      tputs(tgetstr("le", NULL), 1, my_putchar);
      *i -= 2;
    }
    else
      --(*i);
  }
}

static void ctrl_arrow(char *buff, char buff2, int *i)
{
  size_t comp = *i;

  if (buff2 == 2)
  {
    if (*i > 0)
    {
      tputs(tgetstr("le", NULL), 1, my_putchar);
      *i -= 2;
    }
    else
      --(*i);
  }

  if (buff2 == 6)
  {
    if (comp < strlen(buff))
      tputs(tgetstr("nd", NULL), 1, my_putchar);
    else
      --(*i);
  }

  if (buff2 == 14)
    --(*i);

  if (buff2 == 16)
    --(*i);
}

static void ctrl_shortcut_ADE(char *buff, char buff2, int *i)
{
  if (buff2 == 1)
  {
    tputs(tgetstr("rc", NULL), 1, my_putchar);
    *i = -1;
  }

  if (buff2 == 4)
  {
    tputs(tgetstr("dc", NULL), 1, my_putchar);
    memmove(buff + *i, buff + *i + 1, strlen(buff) - *i + 1);
    --(*i);
  }

  if (buff2 == 5)
    tputs(tgetstr("dc", NULL), 1, my_putchar);
}

static void ctrl_shortcut_KL(char *buff, char buff2, int *i)
{
  if (buff2 == 11)
  {
    tputs(tgetstr("ce", NULL), 1, my_putchar);
    for (size_t j = *i; j < strlen(buff); ++j)
      buff[j] = '\0';
    --(*i);
  }

  if (buff2 == 12)
  {
    tputs(tgetstr("cl", NULL), 1, my_putchar);
    write(STDOUT_FILENO, buff, strlen(buff));
    *i = strlen(buff) - 1;
  }
}

static void ctrl_shortcut(char *buff, char buff2, int *i)
{
  ctrl_shortcut_ADE(buff, buff2, i);
  ctrl_shortcut_KL(buff, buff2, i);
}

static void backspace(char *buff, int *i)
{
  --(*i);
  tputs(tgetstr("le", NULL), 1, my_putchar);
  tputs(tgetstr("dc", NULL), 1, my_putchar);
  buff[(*i)] = '\0';
}

static void write_char(char *buff, char *buff2, int *i)
{
  if (buff[(*i)] == '\0')
  {
    write(STDOUT_FILENO, buff2, strlen(buff2));
    buff[(*i)] = buff2[0];
  }
  else
  {
    memmove(buff + *i + 1, buff + *i, strlen(buff) - *i);
    buff[(*i)] = buff2[0];
    write(STDOUT_FILENO, buff2, strlen(buff2));
  }
}

char *readline(char *ps)
{
  int    c;
  char   *psx;
  char   *buff = NULL;
  char   *buff2 = NULL;
  char   *type = getenv("TERM");
  struct termios original_term;

  tcgetattr(STDIN_FILENO, &original_term);
  psx = set_prompt(ps);
  write(STDOUT_FILENO, psx, strlen(psx));
  write(STDOUT_FILENO, " " , 1);
  free(psx);
  buff = calloc(BUFFER_SIZE, sizeof (char));
  buff2 = calloc(2, sizeof (char));
  init_term();
  tgetent(buff2, type);
  tputs(tgetstr("sc", NULL), 1, my_putchar);
  tputs(tgetstr("im", NULL), 1, my_putchar);

  for (int i = 0; ((c = read(STDIN_FILENO, buff2, 1)) > 0) && (i < 512); ++i)
    if (read_user_input(buff, buff2, &i))
      break;

  tputs(tgetstr("ei", NULL), 1, my_putchar);
  tcsetattr(STDIN_FILENO, TCSANOW, &original_term);
  free(buff2);
  write(STDOUT_FILENO, "\n", 1);

  return buff;
}
