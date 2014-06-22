#ifndef AST_H
# define AST_H

# include "ast_struct.h"
# include "free_long_struct.h"
# include "free_rule.h"
# include "free_struct.h"
# include "list_add.h"
# include "shell_cmd.h"
# include "struct_create.h"
# include "union.h"
# include "rule_case.h"
# include "rule.h"
# include "../builtins/builtins.h"
# include <string.h>
/*
** ************************************************************************* **
**                               MACRO                                       **
** ************************************************************************* **
*/
# define IS_AND_OR(Str)                         \
(!strcmp(Str, "&&") ||                          \
 !strcmp(Str, "||"))

# define IS_AND(Str) (!strcmp(Str, "&&"))

# define IS_OR(Str) (!strcmp(Str, "||"))

# define IS_PIPELINE(Str) (!strcmp(Str, "|"))

# define IS_SPECIAL_CHAR(Str)                   \
(!strcmp(Str, ";") ||                           \
 !strcmp(Str, "&") ||                           \
 !strcmp(Str, "\n"))

# define IS_SHELL_CMD(Str)                      \
(!strcmp(Str, "(") ||                           \
 !strcmp(Str, "{") ||                           \
 !strcmp(Str, "if") ||                          \
 !strcmp(Str, "for") ||                         \
 !strcmp(Str, "case") ||                        \
 !strcmp(Str, "until") ||                       \
 !strcmp(Str, "while"))

# define IS_FUNCDEC(Token)                      \
(NULL != Token &&                               \
 (!strcmp((Token)->token, "function") ||        \
  (NULL != (Token)->next &&                     \
   !strcmp((Token)->next->token, "("))))

# define IS_REDIRECTION(Str)                    \
(!strcmp(Str, ">") ||                           \
 !strcmp(Str, ">>") ||                          \
 !strcmp(Str, "<") ||                           \
 !strcmp(Str, "<<") ||                          \
 !strcmp(Str, "<<-") ||                         \
 !strcmp(Str, ">&") ||                          \
 !strcmp(Str, "<&") ||                          \
 !strcmp(Str, "<>") ||                          \
 !strcmp(Str, ">|"))

# define EXIT_AND_OR(Str)                       \
(!strcmp(Str, ";") ||                           \
 !strcmp(Str, "&") ||                           \
 !strcmp(Str, "\n"))

# define EXIT_PIPELINE(Str)                     \
(EXIT_AND_OR(Str) ||                            \
 !strcmp(Str, "&&") ||                          \
 !strcmp(Str, "||"))

# define EXIT_CMD(Str)                          \
(EXIT_PIPELINE(Str) ||                          \
 !strcmp(Str, "|"))

# define EXIT_IF_CONDITION(Str) (!strcmp(Str, "then"))

# define EXIT_IF_GROUP(Str)                     \
(!strcmp(Str, "elif") ||                        \
 !strcmp(Str, "else") ||                        \
 !strcmp(Str, "fi"))

# define EXIT_DO_CONDITION(Str) (!strcmp(Str, "do"))

# define EXIT_DO_GROUP(Str) (!strcmp(Str, "done"))

# define EXIT_CASE_ITEM(Token)                  \
(!strcmp((Token)->token, "esac") ||             \
 (!strcmp((Token)->token, ";") &&               \
  NULL != (Token)->next &&                      \
  strcmp((Token)->next->token, ";")))

# define IS_ASSIGNEMENT_WORD(Str) (strchr(Str, '='))

# define IS_BRACKET(Str)                        \
(!strcmp(Str, "(") || !strcmp(Str, "{"))        \

# define IS_NUMBER(Str)                         \
(!strcmp(Str, "0") ||                           \
 !strcmp(Str, "1") ||                           \
 !strcmp(Str, "2") ||                           \
 !strcmp(Str, "3") ||                           \
 !strcmp(Str, "4") ||                           \
 !strcmp(Str, "5") ||                           \
 !strcmp(Str, "6") ||                           \
 !strcmp(Str, "7") ||                           \
 !strcmp(Str, "8") ||                           \
!strcmp(Str, "9"))


# define EXIT_SIMPLE_CMD(Str)                   \
(IS_SPECIAL_CHAR(Str) ||                        \
 IS_PIPELINE(Str) || IS_AND_OR(Str))
#endif /* AST_H */
