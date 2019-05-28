#include <stdio.h>
#include <string.h>
#include "cstdlib/std.h"
#include "cstdlib/tree.h"

/*! \file
    \brief This header file contains all the macros nessecery for the testsuite.
*/

struct test_data{
  const char * path;
  int(*test_function)(FILE * stream);
  size_t flags;
};

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)
#ifdef TEST
#define ADD_TEST_FUNCTION(test_tree, name) \
  __attribute__((constructor)) \
  void __init_##name__(){ \
    tree_add(test_tree, (gcmp_t) strcmp, #name, HEAPIFY((struct test_data){.test_function = name, .path = __FILE__ ":" LINE_STRING "::" #name }));\
  }
#else
#define ADD_TEST_FUNCTION(test_tree, name)
#endif

extern struct tree *ALL_TESTS;

#define TEST_FUNCTION(name, stream) \
  int name(FILE * stream); \
  ADD_TEST_FUNCTION(&ALL_TESTS, name) \
  int name(FILE * stream)
