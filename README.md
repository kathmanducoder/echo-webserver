# http_webserv

## Description
A web server in C++ that reads the incoming HTTP request header, creates an HTML with CSS style using Bootstrap framework with the header contents and then responds back to client with that HTML.

## Installation
The project comes with a Makefile. Please follow the steps below to make the executable and launch the server.

```
➜  http_webserv git:(main) ✗ make
g++ -c HTTPServer.cpp -o HTTPServer.o
g++ -o http_webserv main.o HTTPServer.o HTMLBuilder.o
➜  http_webserv git:(main) ✗ ./http_webserv
Wed Mar  1 20:33:49 2023 -> http_webserv started on port 8080

```

The webserver runs on port 8080. Now go to your browser and type localhost:8080. You will see a screenshot as below.

## Screenshot
![Screenshot](https://user-images.githubusercontent.com/125407887/222306855-4da2e369-ac36-4a63-92b6-5ee7521e17fa.png)
