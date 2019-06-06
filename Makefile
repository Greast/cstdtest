DIR = cstdlib .
LIB = pthread std
CFLAGS= -DTEST $(addprefix  -I, $(DIR)) -g3 -pedantic -Wall -Werror -Wextra  -Wuninitialized -Wmaybe-uninitialized -Werror=unused-function $(addprefix -L, $(DIR)) $(addprefix -l, $(LIB))
NAME = test
TESTS = tests/list.o

test : test.o $(TESTS) $(FILES)
	$(MAKE) static -C cstdlib
	$(CC) -o $@.out $^ $(CFLAGS)

shared : test.o $(TESTS)
	$(MAKE) shared -C cstdlib
	$(CC) -o lib$(NAME).so $^ -shared $(CFLAGS)


static: test.o $(TESTS)
	$(MAKE) static -C cstdlib
	ar -x cstdlib/libstd.a
	ar -rc lib$(NAME).a $^ *.o


run-test : test
	./test.out

clean:
	$(MAKE) clean -C cstdlib -i
	rm *.o  *.out *.a *so
