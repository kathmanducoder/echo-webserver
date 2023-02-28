/*
 * A simple web server in C that responds back with contents of the incoming
 * HTTP header in its 200 OK response body.
 */

#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

#define PORT 8080

int main() {
    int server_fd;
    struct sockaddr_in server_addr;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, SOMAXCONN) != 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}
