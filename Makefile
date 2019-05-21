DIR = cstdlib
LIB = pthread std
CFLAGS= -DTEST $(addprefix  -I, $(DIR))  -g3 -pedantic -Wall -Werror -Wextra  -Wuninitialized -Wmaybe-uninitialized -Werror=unused-function $(addprefix -L, $(DIR)) $(addprefix -l, $(LIB))

FILES = test.o

test : $(FILES)
	$(MAKE) static -C cstdlib
	$(CC) -o $@.out $^ $(CFLAGS)

clean:
	rm *.o  *.out ; $(MAKE) clean -C cstdlib
