#include "SocketConnection.hpp"

#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sstream>

int sfd;

SocketConnection::SocketConnection() {
	int errcode;

	while ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		sleep(1);
	}

	struct addrinfo hints{};
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	hints.ai_protocol = 0;

	struct addrinfo *info;
	errcode = getaddrinfo("10.10.247.147", "1337", &hints, &info);
	if (errcode != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(errcode));
		exit(EXIT_FAILURE);
	}

	if ((errcode = connect(sfd, info->ai_addr, info->ai_addrlen) != 0)) {
		// TODO Error
	}

	freeaddrinfo(info);
}

SocketConnection::~SocketConnection() {
	close(sfd);
}

void SocketConnection::sendDistance(const double distance) {
	std::stringstream ss;
	ss << "d" << distance;
	send(ss.str().c_str());
}

void SocketConnection::sendAngle(const double angle) {
	std::stringstream ss;
	ss << "a" << angle;
	send(ss.str().c_str());
}

void SocketConnection::send(const char *string) {
	write(sfd, string, strlen(string));
	write(sfd, "\n", 1);
}
