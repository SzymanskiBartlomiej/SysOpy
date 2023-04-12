CC=gcc
CFLAGS =-Wall


all: siginfo resethand nodefer

siginfo:
	$(CC) $(CFLAGS) -c siginfo.c
	$(CC) siginfo.o -o siginfo

resethand:
	$(CC) $(CFLAGS) -c resethand.c
	$(CC) resethand.o -o resethand

nodefer:
	$(CC) $(CFLAGS) -c nodefer.c
	$(CC) nodefer.o -o nodefer

clean:
	rm -rf siginfo *.o resethand nodefer