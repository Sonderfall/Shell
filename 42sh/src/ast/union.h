#ifndef UNION_H
# define UNION_H

# include "ast_struct.h"

/**
** @brief create a node prefix
** @param prefix value of the prefix
** @param type type of prefix
** @return node of prefix
*/
s_prefix *create_prefix(u_uprefix prefix, e_type_element type);

/**
** @brief create a node element
** @param element value of the element
** @param type type of the element
** @return node of the element
*/
s_element *create_element(u_uelement element, e_type_element type);

/**
** @brief free a node prefix and all his child
** @param prefix top node to free
*/
void free_prefix(s_prefix *prefix);

/**
** @brief free a node element and all his child
** @param element top node to free
*/
void free_element(s_element *element);

#endif /* !UNION_H */
