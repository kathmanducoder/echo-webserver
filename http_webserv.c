/*
 * A simple web server in C that responds back with contents of the incoming
 * HTTP header in its 200 OK response body.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int main() {
    int server_fd;

    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}
