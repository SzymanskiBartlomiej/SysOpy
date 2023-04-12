CC=gcc
CFLAGS =-Wall


all: sender catcher

sender:
	$(CC) $(CFLAGS) -c sender.c
	$(CC) sender.o -o sender

catcher:
	$(CC) $(CFLAGS) -c catcher.c
	$(CC) catcher.o -o catcher

clean:
	rm -rf catcher sender *.o