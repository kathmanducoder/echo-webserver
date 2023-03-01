http_webserv: main.o
	g++ -o http_webserv main.o

main.o: main.cpp
	g++ -c main.cpp -o main.o

clean:
	rm -f http_webserv *.o
