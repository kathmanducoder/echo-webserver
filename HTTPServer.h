#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <arpa/inet.h>

class HTTPServer {
    private:
        int server_port;
        int server_fd;
        struct sockaddr_in server_addr;

    public:
        HTTPServer(int port);
        ~HTTPServer();
        void start();
};

#endif