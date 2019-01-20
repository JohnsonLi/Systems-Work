cake: dirinfo.o
	gcc -o out dirinfo.o

dirinfo.o: dirinfo.c
	gcc -c dirinfo.c

run:
	./out $(dir)

clean:
	rm *.o
	rm ./out