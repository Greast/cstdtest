DIR = cstdlib
LIB = pthread std
CFLAGS=-DTEST $(addprefix  -I, $(DIR))  -g3 -pedantic -Wall -Werror -Wextra  -Wuninitialized -Wmaybe-uninitialized -Werror=unused-function $(addprefix -L, $(DIR)) $(addprefix -l, $(LIB))


test : test.o $(FILES)
	$(MAKE) static -C cstdlib
	$(CC) -o $@.out $^ $(CFLAGS)

run-test : test
	./test.out

clean:
	rm *.o  *.out ; $(MAKE) clean -C cstdlib
