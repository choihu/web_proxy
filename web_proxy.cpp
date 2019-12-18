#include "echo_server.h"

void str_to_uint16(char* str, uint16_t* ret) {
    char *end;
    intmax_t val = strtoimax(str, &end, 10);
    *ret = (uint16_t) val;
    return;
}

void dump(char* buf) {
	for(int i = 0; i < strlen(buf); i++) {
		printf("%02x ", buf[i]);
		if((i + 1) % 16 == 0) printf("\n");
	}
	printf("\n");
}

void client_recv(int fd) {
	while(true) {
                const static int BUFSIZE = 1024;
                char buf[BUFSIZE];
                ssize_t received = recv(fd, buf, BUFSIZE - 1, 0);
		printf("client recv msg: ");
		dump(buf);
                if (received == 0 || received == -1) {
                       perror("recv failed");
                       break;
        	}
	}
}

void client_send(int fd) {
	while(true) {
		const static int BUFSIZE = 1024;

		ssize_t sent = send(fd, buf, strlen(buf), 0);
                if (sent == 0) {
                	perror("send failed");
                        break;
                }
	}
}

void web_server_recv(){
}

void web_werver_send(){
}

