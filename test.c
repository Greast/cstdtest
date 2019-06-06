#define _GNU_SOURCE
#include <pthread.h>
#include <signal.h>
#include "test.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"


struct test_function_result{
  const char * string;
  const size_t len;
  const int return_code;
};

void cstdtest_pthread_crash_handler(int signum){
  struct test_function_result tfr = {
    .string = NULL,
    .len = 0,
    .return_code = signum
  };
  pthread_exit(HEAPIFY(tfr));
}

int run_test(FILE * stream, struct test_data * test){
  switch (test->flags) {
    case 0:
      return test->test_function(stream);
  }
  return 0;
}

void * pthread_run_test(void * args){
  struct sigaction action = {
    .sa_flags = SA_RESETHAND,
    .sa_handler = cstdtest_pthread_crash_handler
  };
  sigaction(SIGSEGV, &action, NULL);
  struct test_data * td = args;
  char * buf = NULL;
  size_t len = 0;
  FILE * stream = open_memstream(&buf, &len);
  const int ret = run_test(stream, td);
  fclose(stream);

  struct test_function_result tfr = {
    .string = buf,
    .len = len,
    .return_code = ret
  };
  pthread_exit(HEAPIFY(tfr));
  return NULL;
}

struct complete_tests{
  size_t succeded, failed, skipped;
};

int print_output(FILE * stream, const struct test_data * td, const struct test_function_result * tfr, struct complete_tests *tests){
  if(tfr->return_code){
    ++tests->failed;
    fprintf(stream, ANSI_COLOR_RED "%s : ", td->path);
    if(tfr->string){
      fprintf(stream, "%s\n" ANSI_COLOR_RESET, tfr->string);
    }else{
      fprintf(stream,"%d\n" ANSI_COLOR_RESET, tfr->return_code);
    }
  } else{
    ++tests->succeded;
    fprintf(stream, ANSI_COLOR_GREEN "%s : %s\n" ANSI_COLOR_RESET, td->path, "✓");
  }

  return tfr->return_code;
}

int parrallel_test(FILE* stream, const size_t num_cores, struct list * list){
  pthread_t threads[num_cores];
  const struct test_data * give_data[num_cores];
  memset(give_data, 0, sizeof(give_data));

  struct complete_tests ct = {0,0,0};

  size_t i = 0;
  while(list) {
    void * value = NULL;
    if(!give_data[i] || !pthread_tryjoin_np(threads[i], &value)){
      if(give_data[i]) print_output(stream, give_data[i], value, &ct);
      give_data[i] = ((struct node*)list_remove(&list,0)) -> value;
      pthread_create(threads + i, NULL, pthread_run_test, (void*)give_data[i]);
    }
    i = i + 1 % num_cores;
  }
  for (size_t i = 0; i < num_cores; i++) {
    void * value = NULL;
    if(give_data[i] && !pthread_join(threads[i], &value)){
      if(give_data[i]) print_output(stream, give_data[i], value, &ct);
    }
  }
  fprintf(stream, "Total : %zu, ", ct.succeded + ct.failed + ct.skipped);
  fprintf(stream, ANSI_COLOR_GREEN  "Succeded : %zu, "ANSI_COLOR_RESET, ct.succeded );
  fprintf(stream, ANSI_COLOR_RED    "Failed : %zu, "  ANSI_COLOR_RESET, ct.failed );
  fprintf(stream, ANSI_COLOR_YELLOW "Skipped : %zu\n" ANSI_COLOR_RESET, ct.skipped );
  return 0;
}


struct tree *ALL_TESTS = NULL;

int __test_main(int argc, const char**argv){
  struct tree * tests = ALL_TESTS;
  if(1 < argc){
    tests = NULL;
    for (int i = 1; i < argc; i++) {
      const struct node * value = tree_get(ALL_TESTS, (gcmp_t)(strcmp), argv[i]);
      if(!value) fprintf(stderr, "Could not find test : %s\n", argv[i] );
      else tree_add(&tests, (gcmp_t)strcmp, argv[i], value->value);
    }
  }
  struct list * list = tree_nodes(tests);
  const int ret = parrallel_test(stderr, 1, list);
  return ret;
}

__attribute__((weak))
int main(int argc, char const *argv[]) {
  return __test_main(argc,argv);
}
