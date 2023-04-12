CC=gcc
CFLAGS =-Wall


all: main exec test1 test2 test3

main:
	$(CC) $(CFLAGS) -c main.c
	$(CC) main.o -o main

exec:
	$(CC) $(CFLAGS) -c exec.c
	$(CC) exec.o -o exec


test1:  main
	echo precyzja = 0.000001, n = 5000 > raport.txt
	(time ./main 0.000001 5000) >> raport.txt 2>&1

test2:  main
	echo >> raport.txt
	echo precyzja = 0.000001, n = 7000 >> raport.txt
	(time ./main 0.000001 7000) >> raport.txt 2>&1

test3:  main
	echo >> raport.txt
	echo precyzja = 0.00000001, n = 8000 >> raport.txt
	(time ./main 0.00000001 8000) >> raport.txt 2>&1


clean:
	rm -rf main *.o exec *.txt