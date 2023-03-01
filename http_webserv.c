/*
 * A simple web server in C that responds back with contents of the incoming
 * HTTP header in its 200 OK response body.
 */

#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define SOCK_DATA_BUFFER 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t server_addr_len, client_addr_len;
    char *read_buffer = NULL;
    char write_buffer[1024];
    char html_response[1024];
    ssize_t num_bytes_read;
    int snprintf_len;

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

    /* Allocate memory for buffers */
    if((read_buffer = (char *) malloc(SOCK_DATA_BUFFER * sizeof(char))) == NULL) {
        perror("http_webserv (malloc failed)");
        exit(EXIT_FAILURE);
    }


    /* Enter an infinite loop to listen for (and process) incoming connectsions */
    for(;;) {
        client_addr_len = sizeof(client_addr);

        if((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t*)&client_addr_len)) < 0) {
            perror("http_webserv (accept failed)");
            continue;
        }

        printf("Connection request from: %s\n", inet_ntoa(client_addr.sin_addr));
        if((num_bytes_read = read(client_fd, read_buffer, SOCK_DATA_BUFFER)) < 0) {
            perror("http_webserv (read failed)");
            continue;
        }

        /* End read buffer with null terminating character */
        read_buffer[num_bytes_read] = '\0';
        printf("Bytes read from client = %zd. Message is [%s]\n", num_bytes_read, read_buffer);

        /* Write the read buffer back to the client */
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
            perror("http_webserv (write failed)");
        }
    }

    free(read_buffer);
    return 0;
}
