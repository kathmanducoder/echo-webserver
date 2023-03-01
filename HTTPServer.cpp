#include <exception>
#include <iostream>
#include <sys/socket.h>

#include "HTTPServer.h"

HTTPServer::HTTPServer(int port) {
    this->server_port = port;

    /* Create server socket */
    if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "http_webserv (socket failed).";
        throw std::runtime_error("http_webserv (socket failed).");
    }

    /* Attach socket to server_port */
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    this->server_addr.sin_port = htons(this->server_port);
    if (bind(this->server_fd, (struct sockaddr*)&this->server_addr, sizeof(this->server_addr)) != 0) {
        std::cerr << "http_webserv (bind failed).";
        throw std::runtime_error("http_webserv (bind failed).");
    }
}

HTTPServer::~HTTPServer() {}

void HTTPServer::run() {
    /* Listen for incoming connections */
    if (listen(this->server_fd, SOMAXCONN) != 0) {
        std::cerr << "http_webserv (listen failed).";
        throw std::runtime_error("http_webserv (listen failed).");
    }

    std::cout << "Webserver started. Listening on port " << this->server_port << std::endl;

    for(;;) {
        
    }
}