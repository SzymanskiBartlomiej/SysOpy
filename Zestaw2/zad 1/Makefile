CC=gcc
CFLAGS =-Wall


all: lib sys time

lib:
	$(CC) $(CFLAGS) -c lib.c
	$(CC) lib.o -o lib
sys:
	$(CC) $(CFLAGS) -c sys.c
	$(CC) sys.o -o sys

time: lib sys
	echo "Lib Time Result" >> pomiar_zad_1.txt
	(time ./lib a ! lib.c result.txt) >> pomiar_zad_1.txt 2>&1
	echo "" >> pomiar_zad_1.txt
	echo "Sys Time Result" >> pomiar_zad_1.txt
	(time ./sys a ! lib.c result.txt) >> pomiar_zad_1.txt 2>&1



clean:
	rm sys lib *.o *.txt