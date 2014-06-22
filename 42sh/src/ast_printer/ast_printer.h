#ifndef AST_PRINTER_H
# define AST_PRINTER_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "../ast/ast_struct.h"
# include "read_tree.h"

/**
** @brief Put a tag in a node
** @param label The name of the node
** @param tag The tag of the node
*/
char *write_label(char *label, void *tag);

/**
** @brief Create the link a -> b in the dot file
** @param a The 1st string
** @param b The string dest
*/
void write_link(char *a, char *b);


/**
** @brief Read the tree and create the dot file, with node_list
** @param node_list list
*/
void create_ast_dot(s_list *node_list);


#endif /* !AST_PRINTER_H */
