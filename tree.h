/*! \file */
#ifndef _C_STD_LIB_TREE_H_
#define _C_STD_LIB_TREE_H_
#include "std.h"

/*!
    \brief Internal struct for containing tree data.
*/
struct node{
  const void * key; //!< The key, this is the value compare against, when searching the tree.
  void * value; //!< The Value, this is the value contained by the key.
};

/*!
    \brief Struct for for a given tree node.
*/
struct tree{
  struct tree *lhs, //!< Left hand child.
  *rhs; //!< Right hand child.
  struct node node; //!< The key, value pair.
};

/*! \fn int tree_add(struct tree ** tree, int(*compare)(const void* lhs, const void* rhs), const void* key, void* value)
    \brief Adds a key value pair, to the given tree, orderd by the given compare function.
    \param tree The tree, which to add the key value pair.
    \param compare The callback function, which to order the tree by.
    \param key The key value, which is used to order the data in the tree.
    \param value Specifes the data to the given key.
*/
int tree_add(struct tree ** tree, int(*compare)(const void* lhs, const void* rhs), const void* key, void* value);

/*! \fn void ** tree_get(struct tree ** tree, int(*compare)(const void* lhs, const void* rhs), const void* key)
    \brief Gets The value by the accociated key.
    \param tree The tree, which to retrive the value from.
    \param compare The callback function, specifies the order of the tree.
    \param key The key, which accociates, the value to be retrived.
*/
void ** tree_get(struct tree ** tree, int(*compare)(const void* lhs, const void* rhs), const void* key);

/*! \fn int tree_join(struct tree* tree, int(*print)(const void* lhs, const void* rhs), FILE* stream, const char* seperator)
    \brief Writes then given tree, with the left->right ordering, to the given stream.
    \param tree The tree, which to write to the stream.
    \param print The callback function, with which to print the key value pairs.
    \param stream The stream which is written to.
*/
int tree_join(struct tree* tree, int(*print)(FILE* stream, const void* lhs, const void* rhs), FILE* stream, const char* seperator);


#endif /* end of include guard: _C_STD_LIB_TREE_H_*/
