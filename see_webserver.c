#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("Error creating socket.");
		return 1;
	}
	return 0;
}
