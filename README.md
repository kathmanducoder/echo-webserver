# echowebserver

## Description
A web server that echoes back the HTTP request by adding CSS style to it using Bootstrap frontend framework.

## Installation
The project comes with a Makefile. Please follow the steps below to make the executable and launch the server.

```
➜  echo-webserver git:(main) ✗ make 
g++ -c main.cpp -o main.o
g++ -c HTTPServer.cpp -o HTTPServer.o
g++ -c HTMLBuilder.cpp -o HTMLBuilder.o
g++ -o echowebserver main.o HTTPServer.o HTMLBuilder.o
➜  echo-webserver git:(main) ✗ ./echowebserver 
Mon Mar  6 12:52:53 2023 -> echowebserver started on port 8080

```

The webserver runs on port 8080. Now go to your browser and type localhost:8080. You will see a screenshot as below.

## Demo Screenshot
![Screenshot](https://user-images.githubusercontent.com/125407887/222942176-dab44d74-3b23-4ded-8bbf-c29a56107d22.png)
