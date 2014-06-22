#ifndef LIST_ADD_H
# define LIST_ADD_H

# include "ast_struct.h"

/**
** @brief add an element and_or to the list
** @param list list where we want add the element
** @param element  element to add
*/
void list_add_element(s_list **list, s_and_or *element);

/**
** @brief add an element command to the pipeline command
** @param list list where we want to add the element
** @param element element to add
*/
void pipeline_add_element(s_pipeline **list, s_cmd *element);

/**
** @brief add an element prefix or element to the simple command
** @param list list where we want to add the element
** @param prefix prefix we want to add
** @param element element we want to add
** @note only one of element or prefix can be set to Not NULL
*/
void simple_cmd_add_element(s_simple_cmd    **list,
                            s_prefix        *prefix,
                            s_element       *element);

#endif /* !LIST_ADD_H */
