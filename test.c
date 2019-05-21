#define _GNU_SOURCE
#include <pthread.h>
#include <signal.h>
#include "test.h"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"


struct test_function_result{
  const char * string;
  const size_t len;
  const int return_code;
};

void pthread_crash_handler(int signum){
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
    .sa_handler = pthread_crash_handler
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

int print_output(FILE * stream, struct test_data * td, struct test_function_result * tfr){
  if(tfr->return_code){
    fprintf(stream, ANSI_COLOR_RED "%s : ", td->path);
    if(tfr->string){
      fprintf(stream, "%s\n" ANSI_COLOR_RESET, tfr->string);
    }else{
      fprintf(stream,"%d\n" ANSI_COLOR_RESET, tfr->return_code);
    }
  } else{
    fprintf(stream, ANSI_COLOR_GREEN "%s : %s\n" ANSI_COLOR_RESET, td->path, "✓");
  }

  return tfr->return_code;
}

int parrallel_test(FILE* stream, const size_t num_cores, struct list * list){
  pthread_t threads[num_cores];
  struct test_data * give_data[num_cores];
  memset(give_data, 0, sizeof(give_data));
  size_t i = 0;
  while(list) {
    void * value = NULL;
    if(!pthread_tryjoin_np(threads[i], &value) || !give_data[i]){
      if(give_data[i]) print_output(stream, give_data[i], value);
      give_data[i] = list_remove(&list,0);
      pthread_create(threads + i, NULL, pthread_run_test, give_data[i]);
    }
    i = i + 1 % num_cores;
  }
  for (size_t i = 0; i < num_cores; i++) {
    void * value = NULL;
    if(!pthread_join(threads[i], &value)){
      if(give_data[i]) print_output(stream, give_data[i], value);
    }
  }
  return 0;
}

struct tree *ALL_TESTS = NULL;

#ifdef main
#define save main
#undef main

int main(int argc, char const *argv[]){
  struct tree * tests = ALL_TESTS;
  if(1 < argc){
    tests = NULL;
    for (int i = 0; i < argc - 1; i++) {
      void ** value = tree_get(tests, (gcmp_t)(strcmp), argv[i]);
      if(!value) fprintf(stderr, "Could not find test : %s\n", argv[i] );
      else tree_add(&tests, (gcmp_t)strcmp, argv[i], *value);
    }
  }
  struct list * list = tree_values(tests);
  return parrallel_test(stderr, 1, list);
}

#define main save
#undef save
#endif
