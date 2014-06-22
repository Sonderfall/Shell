#ifndef READ_TREE_H
# define READ_TREE_H

# include "ast_printer.h"
# include "../ast/ast_struct.h"
# include "read_sh_cmd.h"
# include <unistd.h>
# include <stdlib.h>


/**
** @brief Write instruction to draw an and_or node in the dot file
*/
char *read_and_or(s_and_or *node_and_or);

/**
** @brief Write instruction to draw a shell_cmd node in the dot file
*/
char *read_shell_cmd(s_shell_cmd *node_sh_cmd);

/**
** @brief Write instruction to draw a list node in the dot file
*/
char *read_list(s_list *node_list);

#endif /* !READ_TREE_H */
