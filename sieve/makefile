cake: sieve.o main.o
	gcc sieve.o main.o -lm

sieve.o: sieve.c sieve.h
	gcc -c sieve.c -lm

main.o: main.c
	gcc -c main.c

run:
	./a.out

clean:
	rm *.out
	rm *.o