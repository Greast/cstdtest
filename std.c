#include "std.h"

void * safe_memcpy(void * destination, const void* source, const size_t size){
  if(!destination || !source) return NULL;
  return memcpy(destination, source, size);
}
