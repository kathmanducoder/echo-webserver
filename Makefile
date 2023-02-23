kath_webserv: kath_webserv.o
	gcc kath_webserv.o -o kath_webserv

kath_webserv.o: kath_webserv.c
	gcc -c kath_webserv.c -o kath_webserv.o

clean:
	rm -f kath_webserv *.o
