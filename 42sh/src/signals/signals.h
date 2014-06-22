#ifndef SIGNALS_H
# define SIGNALS_H

# include <stdlib.h>
# include <signal.h>

void sig_handler(int sig);

void init_sigaction(void);

#endif /* !SIGNALS_H */
