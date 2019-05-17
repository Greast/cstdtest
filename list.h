/*! \file */
#ifndef _C_STD_LIB_LIST_H_
#define _C_STD_LIB_LIST_H_
#include "std.h"


/*!
  \brief List struct used to reprecent type-less lists.
*/
struct list{
  struct list * next; //!< The next list node. in line.
  void * value; //!< The value contained by this list node.
};

/*!
  \fn int list_add(struct list ** list, void * value)
  \brief This function adds a new node, to already exsisting list, containing the given value.
  \param list The list which to add an element at the front.
  \param value The value which is added to the given list.
*/
int list_add(struct list ** list, void * value);

/*!
  \fn void** list_get(struct list * list, const size_t index)
  \brief Get an element from the list by index.

  This function, gets a value from the given list, should the given index be bigger then the list, it will return NULL.
  \param list The list, from which to retrive the value.
  \param index The index at which the value supposedly exists.
*/
void** list_get(struct list * list, const size_t index);

/*!
  \fn void* list_remove(struct list ** list, const size_t index)
  \brief Remove an element fron the list by index.

  This function, removes an element by index, from the list and returns its contained value. Should the given index be larger the then the list, return NULL.
  \param list The list from which, the value is to be removed.
  \param index The index where the value supposedly exists.
*/
void* list_remove(struct list ** list, const size_t index);

/*!
  \fn int list_join(struct list * list, int(*print)(FILE* stream, const void *value), FILE * stream, const char * seperator)
  \brief Print the list.

  This function, prints the given list, to the given stream, vi the given callback function and seperator.
  \param list The list which to print.
  \param print The callback, which is used to print the given values from the list.
  \param stream The file stream, which the the function prints too.
  \param seperator The seperator, the string which notes the seperation, between individual list nodes.
*/
int list_join(struct list * list, int(*print)(FILE* stream, const void *value), FILE * stream, const char * seperator);

/*!
  \fn int list_reverse(struct list * list)
  \brief Reverse the list

  \param list The list to be Reversed.
*/
int list_reverse(struct list * list);

#endif /* end of include guard: _C_STD_LIB_LIST_H_ */
