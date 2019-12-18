#include "web_proxy.h"

void usage() {
	printf("syntax: web_proxy <tcp port> <ssl port>\n");
	printf("example: web_proxy 8080 4433\n");
}

int main(int argc, char* argv[]) {
	if(argc != 3) {
		usage();
		return -1;
	}
	int tcp_port;
	int ssl_port;
	str_to_uint16(argv[1], &tcp_port);
	str_to_uint16(argv[2], &ssl_port);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
                perror("socket failed");
                return -1;
        }

        int optval = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,  &optval , sizeof(int));
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        memset(addr.sin_zero, 0, sizeof(addr.sin_zero));

        int res = bind(sockfd, reinterpret_cast<struct sockaddr*>(&addr), sizeof(struct sockaddr));
        if (res == -1) {
                perror("bind failed");
                return -1;
        }

        res = listen(sockfd, 2);
        if (res == -1) {
                perror("listen failed");
                return -1;
        }

        while (true) {
                struct sockaddr_in addr;
                socklen_t clientlen = sizeof(sockaddr);
                int child = accept(sockfd, reinterpret_cast<struct sockaddr*>(&addr), &clientlen);

		if(child < 0) {
			perror("Error on accpet");
			break;
		}
		thread t1(client_recv, sockfd);
		thread t2(client_send, sockfd);

		t1.detach();
		t2.join();
		print("!");
	}
	return 0;
}
