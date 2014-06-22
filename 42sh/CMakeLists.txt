cmake_minimum_required (VERSION 2.6)

project (42sh C)

file(GLOB AST src/ast/free_long_struct.c src/ast/free_rule.c 
src/ast/free_struct.c src/ast/list_add.c src/ast/rule.c 
src/ast/rule_case.c src/ast/shell_cmd.c src/ast/struct_create.c src/ast/union.c)

file(GLOB AST_PRINTER src/ast_printer/ast_printer.c src/ast_printer/read_sh_cmd.c 
src/ast_printer/read_tree.c)

file(GLOB EXECUTION src/execution/execute_cmd.c src/execution/execute_list.c 
src/execution/execute_pipe.c src/execution/execute_redirect.c
src/execution/execute_rule.c src/execution/execute_case.c)

file(GLOB LEXER src/lexer/group_lexer.c src/lexer/lexer.c
src/lexer/list_token.c src/lexer/quoting.c src/lexer/dollar.c
src/lexer/getlineps2.c)

file(GLOB MAIN src/main/main.c src/main/parser_options.c)

file(GLOB PARSER src/parser_case.c src/parser/parser_command.c
  src/parser/parser_error.c src/parser/parser_global.c
  src/parser/parser_rules.c src/parser/parser_rules_for.c
  src/parser/parser_bracket.c src/parser/parser_element.c
  src/parser/parser_case.c src/parser/parser_redirection.c)

file(GLOB PROMPT src/prompt/prompt.c)

file(GLOB BUILTINS src/builtins/builtins.c 
src/builtins/builtin_cd.c src/builtins/builtin_export.c
src/builtins/builtin_exit.c src/builtins/builtin_source.c
src/builtins/builtin_echo.c)

file(GLOB READLINE src/readline/readline.c src/readline/readline_init.c)

file(GLOB SUBSTITUTION src/substitution/dquote_sub.c src/substitution/my_int.c 
src/substitution/var_sub.c src/substitution/init_var.c)

file(GLOB TILDE src/tilde/tilde.c)

add_executable(42sh ${AST} ${AST_PRINTER} ${EXECUTION} ${LEXER} ${MAIN}
${PARSER} ${PROMPT} ${SUBSTITUTION} ${READLINE} ${BUILTINS} ${TILDE})
