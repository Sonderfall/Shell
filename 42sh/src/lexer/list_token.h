#ifndef LIST_TOKEN_H
# define LIST_TOKEN_H

# include <stdlib.h>
# include <string.h>

typedef enum type_token
{
  TOK_NEWLINE,
  TOK_SEMICOLON,
  TOK_OPERATOR,
  TOK_NUMBER,
  TOK_WORD,
  TOK_D_QUOTE,
  TOK_ARITHMETIC,
  TOK_VARIABLE
} e_type_token;

typedef struct tokens s_tokens;
struct tokens
{
  e_type_token type;
  char         *token;
  s_tokens     *next;
  s_tokens     *tail;
};

/**
** @brief Add a new node token in the end of the list
** @param token the value of char *token field, in the token node
** @param type the type of the token
** @param list the list where the node will be add
** @return the pointer to the list
*/
s_tokens *token_add(char *token, e_type_token type, s_tokens *list);

/**
** @brief Free the head of the list
** @param list where the head will be eaten
** @return a pointer to the new list (without the head), or NULL
*/
s_tokens *eat_token(s_tokens *list);

s_tokens *get_next_line(s_tokens *list);
#endif /* !LIST_TOKEN_H */
