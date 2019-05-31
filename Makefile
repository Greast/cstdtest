DIR = cstdlib
LIB = pthread std
CFLAGS= -DTEST $(addprefix  -I, $(DIR)) -fPIC -g3 -pedantic -Wall -Werror -Wextra  -Wuninitialized -Wmaybe-uninitialized -Werror=unused-function $(addprefix -L, $(DIR)) $(addprefix -l, $(LIB))
NAME = test

test : test.o $(FILES)
	$(MAKE) static -C cstdlib
	$(CC) -o $@.out $^ $(CFLAGS)

shared : test.o
	$(MAKE) shared -C cstdlib
	$(CC) -o lib$(NAME).so $^ -shared $(CFLAGS)


static: test.o
	$(MAKE) static -C cstdlib
	cp cstdlib/libstd.a lib$(NAME).a
	ar q lib$(NAME).a $^
	#ar -rc lib$(NAME).a $^ $(find -name cstdlib "*.o")


run-test : test
	./test.out

clean:
	$(MAKE) clean -C cstdlib -i
	rm *.o  *.out *.a *so
