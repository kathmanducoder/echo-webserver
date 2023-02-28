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
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t server_addr_len, client_addr_len;

    /* Create server socket */
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("http_webserver (socket failed)");
        exit(EXIT_FAILURE);
    }

    /* Attach socket to port 8080 */
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);
    server_addr_len = sizeof(server_addr);
    if (bind(server_fd, (struct sockaddr*)&server_addr, server_addr_len) != 0) {
        perror("http_webserv (bind failed)");
        exit(EXIT_FAILURE);
    }

    /* Listen for incoming connections */
    if (listen(server_fd, SOMAXCONN) != 0) {
        perror("http_webserv (listen failed)");
        exit(EXIT_FAILURE);
    }

    printf("Webserver started. Listening on port = %d\n", PORT);

    /* Enter an infinite loop to listen for (and process) incoming connectsions */
    for(;;) {
        client_addr_len = sizeof(client_addr);

        if((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t*)&client_addr_len)) < 0) {
            perror("http_webserv (accept failed)");
        }

        printf("Connection request from: %s\n", inet_ntoa(client_addr.sin_addr));

    }

    return 0;
}
