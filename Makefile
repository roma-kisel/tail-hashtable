# Makefile
# Solution: IJC-DU2, 25.04.2016
# Author: Roman Kiselevich, FIT
# Compiler: gcc 4.8.4

CC			= gcc
CFLAGS 		= -std=c99 -Wall -pedantic -Wextra
CPLUS		= g++
CPPFLAGS	= -std=c++11 -Wall -pedantic

ERROR		= error
HASHFUNC	= hash_function_default
HTABINIT	= htab_init
HTABINIT2	= htab_init2
HTABRM		= htab_remove
HTABCLR		= htab_clear
HTABFREE	= htab_free
HTABFOREACH	= htab_foreach
HTABADD		= htab_lookup_add
IO			= io
TAIL		= tail
TAIL2		= tail2

WORDCOUNT	= wordcount

LIBNAME		= libhtable

STATLIBOBJS	= $(HASHFUNC).o $(HTABINIT).o $(HTABINIT2).o $(HTABRM).o \
			$(HTABCLR).o $(HTABFREE).o $(HTABFOREACH).o $(HTABADD).o

all: $(TAIL) $(TAIL2) $(WORDCOUNT) $(WORDCOUNT)-dynamic $(LIBNAME).a $(LIBNAME).so

# tail
$(TAIL): $(TAIL).o $(ERROR).o
	$(CC) $(CFLAGS) $^ -o $@

$(TAIL).o: $(TAIL).c
	$(CC) $(CFLAGS) $^ -c
# end of tail

# tail2
$(TAIL2): $(TAIL2).o
	$(CPLUS) $(CPPFLAGS) $^ -o $@

$(TAIL2).o: $(TAIL2).cc
	$(CPLUS) $(CPPFLAGS) $^ -c
#end of tail2

$(ERROR).o: $(ERROR).c
	$(CC) $(CFLAGS) $^ -c

# static library
$(LIBNAME).a: $(STATLIBOBJS)
	ar rcs $@ $^
	ranlib $@

# static library modules
$(HASHFUNC).o: $(HASHFUNC).c
	$(CC) $(CFLAGS) $^ -c

$(HTABINIT).o: $(HTABINIT).c
	$(CC) $(CFLAGS) $^ -c

$(HTABINIT2).o: $(HTABINIT2).c
	$(CC) $(CFLAGS) $^ -c

$(HTABRM).o: $(HTABRM).c
	$(CC) $(CFLAGS) $^ -c

$(HTABCLR).o: $(HTABCLR).c
	$(CC) $(CFLAGS) $^ -c

$(HTABFREE).o: $(HTABFREE).c
	$(CC) $(CFLAGS) $^ -c

$(HTABFOREACH).o: $(HTABFOREACH).c
	$(CC) $(CFLAGS) $^ -c

$(HTABADD).o: $(HTABADD).c
	$(CC) $(CFLAGS) $^ -c
# end of static library modules 

# static wordcount
$(WORDCOUNT): $(WORDCOUNT).o $(ERROR).o $(IO).o $(LIBNAME).a
	$(CC) -static $(WORDCOUNT).o $(ERROR).o $(IO).o -L. -lhtable -o $@

$(WORDCOUNT).o: $(WORDCOUNT).c 
	$(CC) $(CFLAGS) $^ -c

$(IO).o: $(IO).c
	$(CC) $(CFLAGS) $^ -c 
# end of static wordcount

DNMLIBOBJS	= $(HASHFUNC)_d.o $(HTABINIT)_d.o $(HTABINIT2)_d.o $(HTABRM)_d.o \
			$(HTABCLR)_d.o $(HTABFREE)_d.o $(HTABFOREACH)_d.o $(HTABADD)_d.o

# dynamic library
$(LIBNAME).so: $(DNMLIBOBJS)
	$(CC) -shared -fPIC -o $@ $^

$(ERROR)_d.o: $(ERROR).c
	$(CC) -fPIC $(CFLAGS) -c $^ -o $@

# dynamic library modules
$(HASHFUNC)_d.o: $(HASHFUNC).c
	$(CC) -fPIC $(CFLAGS) -c $^ -o $@

$(HTABINIT)_d.o: $(HTABINIT).c
	$(CC) -fPIC $(CFLAGS) -c $^ -o $@

$(HTABINIT2)_d.o: $(HTABINIT2).c
	$(CC) -fPIC $(CFLAGS) -c $^ -o $@

$(HTABRM)_d.o: $(HTABRM).c
	$(CC) -fPIC $(CFLAGS) -c $^ -o $@

$(HTABCLR)_d.o: $(HTABCLR).c
	$(CC) -fPIC $(CFLAGS) -c $^ -o $@

$(HTABFREE)_d.o: $(HTABFREE).c
	$(CC) -fPIC $(CFLAGS) -c $^ -o $@

$(HTABFOREACH)_d.o: $(HTABFOREACH).c
	$(CC) -fPIC $(CFLAGS) -c $^ -o $@

$(HTABADD)_d.o: $(HTABADD).c
	$(CC) -fPIC $(CFLAGS) -c $^ -o $@
#end of dynamic library modules

# dynamic wordcount
$(WORDCOUNT)-dynamic: $(WORDCOUNT)_d.o $(ERROR)_d.o $(IO)_d.o $(LIBNAME).so
	$(CC) -fPIC $(WORDCOUNT).o $(ERROR).o $(IO).o -L. -lhtable -o $@

$(WORDCOUNT)_d.o: $(WORDCOUNT).c 
	$(CC) -fPIC $(CFLAGS) $^ -c -o $@

$(IO)_d.o: $(IO).c
	$(CC) -fPIC $(CFLAGS) $^ -c -o $@
# end of dynamic wordcount

clean:
	rm -f *.o $(LIBNAME).a $(LIBNAME).so $(WORDCOUNT) $(WORDCOUNT)-dynamic $(TAIL) $(TAIL2)