# echo_webserver

## Description
A web server that echo backs the HTTP request by adding CSS style to it using Bootstrap frontend framework.

## Installation
The project comes with a Makefile. Please follow the steps below to make the executable and launch the server.

```
➜  echo_webserver git:(main) make
g++ -c main.cpp -o main.o
g++ -c HTTPServer.cpp -o HTTPServer.o
g++ -c HTMLBuilder.cpp -o HTMLBuilder.o
g++ -o echo_webserver main.o HTTPServer.o HTMLBuilder.o
➜  echo_webserver git:(main) ./echo_webserver 
Sat Mar  4 23:43:14 2023 -> echo_webserver started on port 8080

```

The webserver runs on port 8080. Now go to your browser and type localhost:8080. You will see a screenshot as below.

## Demo Screenshot
![Screenshot](https://user-images.githubusercontent.com/125407887/222942176-dab44d74-3b23-4ded-8bbf-c29a56107d22.png)
