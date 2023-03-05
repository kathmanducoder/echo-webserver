#include <exception>
#include <iostream>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include "HTTPServer.h"
#include "HTMLBuilder.h"

HTTPServer::HTTPServer(int port) {
    this->server_port = port;

    /* Create server socket */
    if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "echo_webserver (socket failed)." << std::endl;
        throw std::runtime_error("echo_webserver (socket failed).");
    }

    /* Attach socket to server_port */
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    this->server_addr.sin_port = htons(this->server_port);
    if (bind(this->server_fd, (struct sockaddr*)&this->server_addr, sizeof(this->server_addr)) != 0) {
        std::cerr << "echo_webserver (bind failed)." << std::endl;
        throw std::runtime_error("echo_webserver (bind failed).");
    }
}

HTTPServer::~HTTPServer() {
    /* Close the socket */
    close(this->server_fd);
}

void HTTPServer::start() {
    int                 client_fd;
    struct sockaddr_in  client_addr;
    socklen_t           client_addr_len;
    time_t              now_time;
    char                *now_str;
    const int           HTTP_REQ_LEN = 1024;
    char                http_req[HTTP_REQ_LEN];
    ssize_t             http_req_num_bytes;
    const int           HTML_LEN = 4096;
    char                html[HTML_LEN];
    ssize_t             html_num_bytes;
    const int           HTTP_RESP_LEN = 8096;
    char                http_resp[HTTP_RESP_LEN];
    ssize_t             http_resp_num_bytes;

    HTMLBuilder         html_builder;

    /* Listen for incoming connections */
    if (listen(this->server_fd, SOMAXCONN) != 0) {
        std::cerr << "echo_webserver (listen failed)." << std::endl;
        throw std::runtime_error("echo_webserver (listen failed).");
    }

    now_time = time(NULL);
    now_str = ctime(&now_time);
    now_str[strlen(now_str) - 1] = '\0';
    std::cout << now_str << " -> " << "echo_webserver started on port " << this->server_port << std::endl;

    for(;;) {
        client_addr_len = sizeof(client_addr);
        if((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t*)&client_addr_len)) < 0) {
            std::cerr << "echo_webserver (accept failed)." << std::endl;
            continue;
        }

        now_time = time(NULL);
        now_str = ctime(&now_time);
        now_str[strlen(now_str) - 1] = '\0';
        std::cout << now_str << " -> " << "Connection request from "<< inet_ntoa(client_addr.sin_addr) << " sockid = " << client_fd << std::endl;
        
        if((http_req_num_bytes = read(client_fd, http_req, sizeof(http_req))) < 0) {
            std::cerr << "echo_webserver (read failed)." << std::endl;
            continue;
        }
        /* End http req buffer with null terminating character */
        http_req[http_req_num_bytes] = '\0';

        if (html_builder.build_html(html, HTML_LEN, http_req, inet_ntoa(client_addr.sin_addr)) != 0) {
            std::cerr << "echo_webserver (build_html failed)." << std::endl;
            continue;
        }

        http_resp_num_bytes = snprintf(http_resp, sizeof(http_resp), "%s\n%s\n%s\n\n%s\n",
                                "HTTP/1.1 200 OK",
                                "Server: echo_webserver",
                                "Content-Type: text/html",
                                html);
        /* Null terminate write buffer */
        http_resp[http_resp_num_bytes] = '\0';

        if(send(client_fd, http_resp, strlen(http_resp), 0) < 0) {
            std::cerr << "echo_webserver (send failed)." << std::endl;
        }

        /* Close client fd */
        close(client_fd);
    }
}