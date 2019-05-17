#include "tree.h"
__attribute__((nonnull(1,2)))
int tree_add(struct tree ** tree, int(*cmp)(const void*, const void*), const void* key, void* value){
  if(!*tree) {
      struct tree new_tree = {
        .node = {
          .key = key,
          .value = value,
        }
      };
      *tree = HEAPIFY(new_tree)
      return 0;
  }
  const int ret = cmp((*tree)->node.key, key);
  if(!ret) return -1;
  struct tree ** child = 0 < cmp ? &(*tree)->rhs : &(*tree)->lhs;
  return tree_add(child, cmp, key, value);
}

__attribute__((nonnull(1,2)))
void ** tree_get(struct tree ** tree, int(*cmp)(const void*, const void*), const void* key){
  if(!*tree) return NULL;
  const int ret = cmp((*tree)->node.key, key);
  if(!ret) {
    return &(*tree)->node.value;
  };
  struct tree ** child = 0 < cmp ? &(*tree)->rhs : &(*tree)->lhs;
  return tree_get(child, cmp, key);
}

__attribute__((nonnull(1,2,3)))
int tree_join(struct tree* tree, int(*print)(const void*, const void*), FILE*stream, const char* sep){
  int sum = 0;
  if(!tree) return sum;
  int ret;
  if(ret = tree_join(tree->lhs, print, stream, sep)){
    sum += ret + fprintf(stream, "%s", sep);
  }
  sum += print(tree->node.key, tree->node.value);

  if(ret = tree_join(tree->rhs, print, stream, sep)){
    sum += ret + fprintf(stream, "%s", sep);
  }
  return sum;
}
