CC=gcc
CFLAGS =-Wall


all: revByChar revByBlock

revByChar:
	$(CC) $(CFLAGS) -c revByChar.c
	$(CC) revByChar.o -o revByChar

revByBlock:
	$(CC) $(CFLAGS) -c revByBlock.c
	$(CC) revByBlock.o -o revByBlock


clean:
	rm -rf revByChar revByBlock *.o