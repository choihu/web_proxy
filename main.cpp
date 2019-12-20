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
	uint16_t tcp_port;
	uint16_t ssl_port;
	str_to_uint16(argv[1], &tcp_port);
	str_to_uint16(argv[2], &ssl_port);
	
	int sockfd = setup_socket(tcp_port, INADDR_ANY, SERVER);
	
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
		thread t1(client_to_web, sockfd);
		thread t2(web_to_client, sockfd);

		t1.detach();
		t2.join();
		printf("!");
	}
	close(sockfd);
	return 0;
}
