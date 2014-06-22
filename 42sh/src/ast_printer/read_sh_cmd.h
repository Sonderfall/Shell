#ifndef READ_SH_CMD_H
# define READ_SH_CMD_H

# include "ast_printer.h"
# include "../ast/ast_struct.h"
# include "read_tree.h"
# include <stdlib.h>
# include <unistd.h>

/**
** @brief Write instruction to draw the rule for in the dot file
*/
char *read_for(s_rule_for *node_for);

/**
** @brief Write instruction to draw the rule while in the dot file
*/
char *read_while(s_rule_while *node_while);

/**
** @brief Write instruction to draw the rule until in the dot file
*/
char *read_until(s_rule_until *node_until);

/**
** @brief Write instruction to draw the rule case in the dot file
*/
char *read_case(s_rule_case *node_case);


/**
** @brief Write instruction to draw the rule if in the dot file
*/
char *read_if(s_rule_if *node_for);

#endif /* !READ_SH_CMD_H */
