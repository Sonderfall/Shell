#ifndef BUILTIN_ALIAS_H_

# define BUILTIN_ALIAS_H_

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

static void record_arg(char *argv);

static int check_arg(int argc, char *argv[]);

int builtin_alias(int argc, char *argv[]);

#endif /* BUILTIN_ALIAS_H_ */
