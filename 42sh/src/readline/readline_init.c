#include "readline.h"

void init_term(void)
{
  struct termios attr;

  tcgetattr(STDIN_FILENO, &attr);
  attr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &attr);
}

int my_putchar(int ch)
{
  char c = ch;
  return write(STDOUT_FILENO, &c, 1);
}
