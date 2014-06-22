#ifndef PARSER_OPTIONS_H
# define PARSER_OPTIONS_H

/**
** @brief print the version of the shell
** @return the return value of the print
*/
int option_version(void);

/**
** @brief run the -O command when running the shell
** @param argv paramaters when running the shell
** @return the return value of the execution
*/
int option_minusO(char *argv);

/**
** @brief run the +O command when running the shell
** @param argv paramaters when running the shell
** @return return value of the execution
*/
int option_plusO(char *argv);

/**
** @brief checks the arguments when running the shell and applies the
**        correct function to it
** @param argc number of paramaters when running the shell
** @param argv paramaters when running the shell
** @return return value of the execution
*/
int parse_args(int argc, char **argv);

#endif /* !PARSER_OPTIONS_H */
