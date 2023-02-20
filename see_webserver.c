#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>

#define PORT 8080

int main(int argc, char *argv[]) {
	int sockfd;
	struct sockaddr_in host_addr;

	// Create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("Error creating socket.");
		return 1;
	}

	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(PORT);
	host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// Bind the socket
	if(bind(sockfd, (struct sockaddr *)&host_addr, sizeof(host_addr)) != 0) {
		perror("Error binding socket");
		return 1;
	}

	return 0;
}
