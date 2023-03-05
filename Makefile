echo_webserver: main.o HTTPServer.o HTMLBuilder.o
	g++ -o echo_webserver main.o HTTPServer.o HTMLBuilder.o

main.o: main.cpp
	g++ -c main.cpp -o main.o

HTTPServer.o: HTTPServer.cpp
	g++ -c HTTPServer.cpp -o HTTPServer.o

HTMLBuilder.o: HTMLBuilder.cpp
	g++ -c HTMLBuilder.cpp -o HTMLBuilder.o

clean:
	rm -f http_webserv *.o
