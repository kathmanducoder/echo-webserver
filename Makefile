http_webserv: http_webserv.o
	g++ http_webserv.o -o http_webserv

http_webserv.o: http_webserv.cpp
	g++ -c http_webserv.cpp -o http_webserv.o

clean:
	rm -f http_webserv *.o
