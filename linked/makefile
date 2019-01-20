cake: linked.o test.o
	gcc linked.o test.o

linked.o: linked.c
	gcc -c linked.c

test.o: test.c
	gcc -c test.c

run:
	./a.out

clean:
	rm *.out
	rm *.o
