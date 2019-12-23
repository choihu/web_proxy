#include "web_proxy.h"

void usage() {
	printf("syntax: web_proxy <tcp port>\n");
	printf("example: web_proxy 8080\n");
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		usage();
		return -1;
	}
	uint16_t tcp_port;
	str_to_uint16(argv[1], &tcp_port);
	int sockfd = setup_socket(tcp_port, INADDR_ANY, SERVER);
        while (true) {
                struct sockaddr_in addr;
                socklen_t clientlen = sizeof(sockaddr);
                int child = accept(sockfd, reinterpret_cast<struct sockaddr*>(&addr), &clientlen);

		if(child < 0) {
			perror("Error on accpet");
			break;
		}
		thread t(client_to_web, sockfd);

		t.detach();
	}
	close(sockfd);
	return 0;
}
