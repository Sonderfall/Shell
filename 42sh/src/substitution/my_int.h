#ifndef MY_INT_H
# define MY_INT_H

# include <stdlib.h>
# include <string.h>

/**
** @brief Calculate the length of an int in base 10
** @param i the int parameter
** @return the length of i
*/
int intlen(int i);

/**
** @brief Convert a int to string
** @param i the int to convert
** @return return the converted value
*/
char *itoa(int i);

#endif /* !MY_INT_H */
