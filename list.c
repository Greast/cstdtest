#include "list.h"
__attribute__((nonnull(1)))
int list_add(struct list ** list, void * value){
  struct list new_list = {
    .next = (*list),
    .value = value,
  };
  struct list * temp_list = HEAPIFY(new_list);
  if(!temp_list) return -1;
  *list = temp_list;
  return 0;
}

void ** list_get(struct list * list, const size_t index){
  if(!list) return NULL;
  for (size_t i = 0; i < index; i++) {
    list = list->next;
    if(!list) return NULL;
  }
  return &list->value;
}
__attribute__((nonnull(2,3)))
int list_join(struct list * list, int(*print)(FILE * stream, const void *), FILE * stream, const char * seperator){
  size_t sum = 0;
  while (list) {
    sum += print(stream, list->value);
    if(list->next) fprintf(strea, seperator);
    list = list->next;
  }
  return sum;
}

__attribute__((nonnull(1)))
void* list_remove(struct list ** list, const size_t size){
  if(!list) return NULL;
  if(size) return list_remove(&(*list)->next, size - 1);
  struct list * temp = *list;
  *list = temp->next;
  void * value = temp->value;
  free(temp);
  return value;
}

int list_reverse(struct list * list){
  struct list * next = *l, * old = NULL;
  while (next) {
    *l = next;
    next = (*l)->next;
    (*l)-> next = old;
    old = *l;
  }
}
