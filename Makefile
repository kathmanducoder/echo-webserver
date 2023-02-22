kc_webserver: kc_webserver.o
	gcc kc_webserver.o -o kc_webserver

kc_webserver.o: kc_webserver.c
	gcc -c kc_webserver.c -o kc_webserver.o

clean:
	rm -f kc_webserver *.o
