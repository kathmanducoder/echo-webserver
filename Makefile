http_webserv: http_webserv.o
	gcc http_webserv.o -o http_webserv

http_webserv.o: http_webserv.c
	gcc -c http_webserv.c -o http_webserv.o

clean:
	rm -f http_webserv *.o
