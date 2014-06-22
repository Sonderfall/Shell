#ifndef AST_STRUCT_H
# define AST_STRUCT_H

# include "../lexer/list_token.h"
# include <stdlib.h>

/*
** ************************************************************************* **
**                               TYPEDEF                                     **
** ************************************************************************* **
*/
typedef struct list             s_list;
typedef struct cmd              s_cmd;
typedef struct and_or           s_and_or;
typedef struct pipeline         s_pipeline;
typedef struct rule_if          s_rule_if;
typedef struct rule_for         s_rule_for;
typedef struct rule_while       s_rule_while;
typedef struct rule_until       s_rule_until;
typedef struct rule_case        s_rule_case;
typedef struct condition        s_condition;
typedef struct simple_cmd       s_simple_cmd;
typedef struct funcdec          s_funcdec;
typedef struct redirection      s_redirection;
typedef struct shell_cmd        s_shell_cmd;
typedef struct case_item        s_case_item;
typedef struct prefix           s_prefix;
typedef struct element          s_element;
typedef struct case_clause      s_case_clause;
typedef struct else_clause      s_else_clause;
typedef union command           u_command;
typedef union shell_command     u_shell_command;
typedef union uprefix           u_uprefix;
typedef union uelement          u_uelement;

/*
** ************************************************************************* **
**                               ENUM                                        **
** ************************************************************************* **
*/
enum type_shell_cmd
{
  LIST,
  RULE_FOR,
  RULE_WHILE,
  RULE_UNTIL,
  RULE_CASE,
  RULE_IF
};

enum type_element
{
  WORD,
  REDIRECTION
};

enum and_or_type
{
  NONE,
  AND,
  OR,
};

enum redirect
{
  SIMPLE_CHEVRON_LEFT,
  DOUBLE_CHEVRON_LEFT,
  SIMPLE_CHEVRON_RIGHT,
  DOUBLE_CHEVRON_RIGHT,
  AMPERSAND_CHEVRON_LEFT,
  AMPERSAND_CHEVRON_RIGHT,
  CHEVRON_HYPHEN,
  CHEVRON_LEFT_RIGHT,
  CHEVRON_PIPE
};

enum command_type
{
  NO_TYPE,
  SIMPLE_COMMAND,
  SHELL_COMMAND,
  FUNCDEC
};

typedef enum command_type       e_command_type;
typedef enum redirect           e_redirect;
typedef enum and_or_type        e_and_or_type;
typedef enum type_element       e_type_element;
typedef enum type_shell_cmd     e_type_shell_cmd;

/*
** ************************************************************************* **
**                               UNION                                       **
** ************************************************************************* **
*/
union uprefix
{
  char          *word;
  s_redirection *redirect;
};

union uelement
{
  char          *word;
  s_redirection *redirect;
};

union shell_command
{
  s_list        *list;
  s_rule_for    *rule_for;
  s_rule_while  *rule_while;
  s_rule_until  *rule_until;
  s_rule_case   *rule_case;
  s_rule_if     *rule_if;
};

union command
{
  s_simple_cmd      *simple_cmd;
  s_shell_cmd       *shell_cmd;
  s_funcdec         *funcdec;
};

/*
** ************************************************************************* **
**                               STRUCTURE                                   **
** ************************************************************************* **
*/
struct list
{
  s_and_or  **and_or;
  size_t    length;
};

struct and_or
{
  s_pipeline    *pipeline;
  s_and_or      *next;
  e_and_or_type connection;
};

struct pipeline
{
  s_cmd         **commands;
  size_t        length;
};

struct cmd
{
  u_command         cmd;
  e_command_type    type;
};

struct prefix
{
  u_uprefix         prefix;
  e_type_element    type;
};

struct element
{
  u_uelement        element;
  e_type_element    type;
};

struct redirection
{
  char          *word;
  e_redirect    type;
  int           ionumber;
};

struct simple_cmd
{
  s_element     **element;
  s_prefix      **prefix;
  size_t        length_prefix;
  size_t        length_element;
};

struct shell_cmd
{
  u_shell_command   cmd;
  e_type_shell_cmd  type;
};

struct funcdec
{
  char          *name;
  char          **argv;
  size_t        argc;
  s_shell_cmd   *cmd;
};

struct rule_while
{
  s_and_or  *condition;
  s_list    *group;
};

struct rule_until
{
  s_list    *group;
  s_and_or  *condition;
};

struct rule_if
{
  s_and_or  *condition;
  s_list    *action;
  s_list    *elseif;
};

struct rule_for
{
  char      *name;
  char      **in;
  size_t    length_in;
  s_list    *group;
};

struct rule_case
{
  char          *name;
  s_case_item   **items;
  size_t        length;
};

struct case_item
{
  char          *value;
  s_list        *group;
};

struct case_clause
{
  s_case_item *item;
};

struct else_clause
{
  s_rule_if *condition;
  s_list    *action;
};

#endif /* !AST_STRUCT_H */
