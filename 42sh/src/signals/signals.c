#include "signals.h"

void sig_handler(int signum)
{
  if (g_shell->pid != 0 && signum == SIGTERM)
  {
    kill(g_shell->pid, SIGTERM);
    exit(EXIT_SUCCESS);
  }
}

void init_sigaction(void)
{
  struct sigaction act;

  act.sa_handler = sig_handler;
}
