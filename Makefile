noopserv: noopserv.o
	gcc noopserv.o -o noopserv

noopserv.o: noopserv.c
	gcc -c noopserv.c -o noopserv.o

clean:
	rm -f noopserv *.o
