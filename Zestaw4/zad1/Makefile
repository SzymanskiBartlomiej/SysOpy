CC=gcc
CFLAGS =-Wall


all: fork exec

fork:
	$(CC) $(CFLAGS) -c fork.c
	$(CC) fork.o -o fork

exec:
	$(CC) $(CFLAGS) -c exec.c
	$(CC) exec.o -o exec

clean:
	rm -rf fork exec *.o