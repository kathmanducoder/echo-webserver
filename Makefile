http_webserv: main.o HTTPServer.o
	g++ -o http_webserv main.o HTTPServer.o

main.o: main.cpp
	g++ -c main.cpp -o main.o

HTTPServer.o: HTTPServer.cpp
	g++ -c HTTPServer.cpp -o HTTPServer.o

clean:
	rm -f http_webserv *.o
