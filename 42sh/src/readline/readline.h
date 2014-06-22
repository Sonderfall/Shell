#ifndef READLINE_H_
# define READLINE_H_

# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <curses.h>
# include <term.h>
# include "../prompt/prompt.h"

# define BUFFER_SIZE 512


void init_term(void);

int my_putchar(int ch);

char *readline(char *ps);

#endif /* !READLINE_H_ */
