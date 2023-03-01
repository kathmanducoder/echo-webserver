#include <exception>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

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

HTTPServer::~HTTPServer() {
    /* Close the socket */
    close(this->server_fd);
}

void HTTPServer::start() {
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len;
    ssize_t num_bytes_read, num_bytes_written;
    const int READ_BUFFER_LEN = 1024;
    const int WRITE_BUFFER_LEN = 1024;
    const int HTML_CONTENT_BUFFER_LEN = 4096;
    char read_buffer[READ_BUFFER_LEN];
    char html_response[HTML_CONTENT_BUFFER_LEN];
    char write_buffer[WRITE_BUFFER_LEN];
    int snprintf_len;

    /* Listen for incoming connections */
    if (listen(this->server_fd, SOMAXCONN) != 0) {
        std::cerr << "http_webserv (listen failed).";
        throw std::runtime_error("http_webserv (listen failed).");
    }

    std::cout << "Webserver started. Listening on port " << this->server_port << std::endl;

    for(;;) {
        client_addr_len = sizeof(client_addr);
        if((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t*)&client_addr_len)) < 0) {
            std::cerr << "http_webserv (accept failed).";
            continue;
        }

        std::cout << "Connection request from "<< inet_ntoa(client_addr.sin_addr) << std::endl;
        
        if((num_bytes_read = read(client_fd, read_buffer, sizeof(read_buffer))) < 0) {
            std::cerr << "http_webserv (read failed).";
            continue;
        }
        /* End read buffer with null terminating character */
        read_buffer[num_bytes_read] = '\0';

        snprintf_len = snprintf(html_response, sizeof(html_response), "%s\n%s\n%s\n",
                                "<html>",
                                read_buffer,
                                "</html>");
        /* Null terminate html response */
        html_response[snprintf_len] = '\0';

        snprintf_len = snprintf(write_buffer, sizeof(write_buffer), "%s\n%s\n%s\n\n%s\n",
                                "HTTP/1.1 200 OK",
                                "Server: http_webserv",
                                "Content-Type: text/html",
                                html_response);
        /* Null terminate write buffer */
        write_buffer[snprintf_len] = '\0';

        if(send(client_fd, write_buffer, strlen(write_buffer), 0) < 0) {
            std::cerr << "http_webserv (send failed).";
        }
    }
}