SHELL=/bin/bash
CC=gcc
CFLAGS=-Wall

all: static shared dynamic test-static test-shared test-dynamic

static: lib_static
	$(CC) $(CFLAGS) main.c library.a -o main_static
shared: lib_shared
	$(CC) $(CFLAGS) main.c library.so -o main_shared -Wl,-rpath=.
dynamic: lib_shared
	$(CC) $(CFLAGS) main.c -D DYNAMIC -o main_dynamic

lib_static: library.c
	$(CC) $(CFLAGS) -c library.c
	ar cr library.a library.o

lib_shared: library.c
	$(CC) $(CFLAGS) -c -fPIC library.c
	$(CC) $(CFLAGS) -shared -o library.so library.o


test-static:  static
	./main_static < commands.txt > results_static.txt


test-shared:  shared
	./main_shared < commands.txt > results_shared.txt

test-dynamic:  static
	./main_dynamic < commands.txt > results_dynamic.txt

clean:
	rm -rf *.o *.a *.so main_static main_shared main_dynamic result*
