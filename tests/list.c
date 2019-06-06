#include "test.h"
#include "std.h"
#include <stdio.h>


TEST_FUNCTION(test_list_add, stream){
  const char * value = "x";
  struct list * list = NULL;
  if(list_add(&list, value)){
    return fprintf(stream, "Could not add string '%s' to list.", value);
  }

  if(strcmp(list->value, value)){
    return fprintf(stream, "Did not add '%s' to list.", value);
  }
  return 0;
}

TEST_FUNCTION(test_list_remove, stream){
  const char * value = "x";
  struct list * list = NULL;
  if(list_add(&list, value)){
    return fprintf(stream, "Could not add string '%s' to list.", value);
  }
  if(strcmp(list_remove(&list, 0), value)){
    return fprintf(stream, "Did not remove '%s' from list.", value);
  }
  return 0;
}

TEST_FUNCTION(test_list_get, stream){
  const char * value = "x";
  struct list * list = NULL;
  if(list_add(&list, value)){
    return fprintf(stream, "Could not add string '%s' to list.", value);
  }
  if(strcmp(*list_get(list, 0), value)){
    return fprintf(stream, "Did not get '%s' from list.", value);
  }
  return 0;
}

TEST_FUNCTION(test_list_join, stream){
  const char * value = "x";
  struct list * list = NULL;
  if(list_add(&list, value)){
    return fprintf(stream, "Could not add string '%s' to list.", value);
  }
  char * buffer = NULL;
  size_t len = 0;
  FILE * file = open_memstream(&buffer, &len);
  if(!list_join(list, (gprint_t)fprintf, file, ",")){
    return fprintf(stream, "list_join didnt print anything.");
  }
  fclose(file);
  if(strcmp(value, buffer)){
    return fprintf(stream, "Expected : '%s'\n Got : '%s'", value, buffer );
  }
  return 0;
}

TEST_FUNCTION(test_list_create, stream){
  const char * value = "x";
  struct list * expected = NULL;
  if(list_add(&expected, value)){
    return fprintf(stream, "Could not add string '%s' to list.", value);
  }
  struct list * result = list_create(1, value);
  if(list_cmp(expected, result, (gcmp_t)strcmp)){
    return fprintf(stream, "Did not recive expected list.");
  }
  return 0;
}

TEST_FUNCTION(test_list_create_macro, stream){
  const char * value = "x";
  struct list * expected = NULL;
  if(list_add(&expected, value)){
    return fprintf(stream, "Could not add string '%s' to list.", value);
  }
  struct list * result = LIST(value);
  if(list_cmp(expected, result, (gcmp_t)strcmp)){
    return fprintf(stream, "Did not recive expected list.");
  }
  return 0;
}
