#include "web_proxy.h"

mutex m;
vector<pair <char*, int>> sk;

int setup_socket(uint16_t port, uint32_t ip_addr) {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
                perror("socket failed");
                return -1;
        }

        uint16_t port;
        str_to_uint16(argv[1], &port);

        int optval = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,  &optval , sizeof(int));
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = htonl(ip_addr);
        memset(addr.sin_zero, 0, sizeof(addr.sin_zero));

	return sockfd;
}

void str_to_uint16(char* str, uint16_t* ret) {
    char *end;
    intmax_t val = strtoimax(str, &end, 10);
    *ret = (uint16_t) val;
    return;
}

void str_to_uint32(char* str, uint16_t* ret) {
    char *end;
    intmax_t val = strtoimax(str, &end, 10);
    *ret = (uint32_t) val;
    return;
}


void dump(char* buf) {
	for(int i = 0; i < strlen(buf); i++) {
		printf("%02x ", buf[i]);
		if((i + 1) % 16 == 0) printf("\n");
	}
	printf("\n");
}

void client_to_web(int fd) {
	vector<pair <char*, int>> sk;
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
		char* host;
		host_check(buf, host);
		bool flg = false;
		m.lock();
		for(vector<pair <char*, int>> iterator::it = sk.begin();
		it != sk.end();
		it++){
			if(!strncmp(host, sk[i].first, strlen(host))) {
				char pk[50];
			        ////
				flg = true;
			}
		}
		m.unlock();
		if(flg) continue;
		else {
			addrinfo *addr_info;
 			if(getaddrinfo(host, "80", NULL, &addr_info) != 0) {
				perror("error during getting ip addr info");
				freeaddrinfo(addr_info);
				continue;
			}
			freeaddrinfo(addr_info);
			uint32_t ip_addr;
			str_to_uint32(addr_info, &ip_addr);
			int web_fd = setup_socket(TCP_PORT, ip_addr);
			////
		}
	}
}

void web_to_client(int fd) {
	while(true) {
		const static int BUFSIZE = 1024;
		char buf[BUFSIZE];

		ssize_t sent = send(fd, buf, strlen(buf), 0);
                if (sent == 0) {
                	perror("send failed");
                        break;
                }
	}
}

void host_check(char *data, char *captured_host) {
	uint8_t ip_header_length, tcp_header_length;
	ip_header_length = (data[0] & 0x0F) * 4;
	tcp_header_length = ((data[ip_header_length + 12] & 0xF0) >> 4) * 4;
	int http_offset = ip_header_length + tcp_header_length;
	int k;
	char method[6][10] = {"GET", "POST", "HEAD", "PUT", "DELETE", "OPTIONS"};
	
	//check tcp segment is http
	for(k = 0; k < 6; k++) {
		if(!memcmp(data + http_offset, method[k], strlen(method[k]))){
			break;
		}	
	}
	int i = 0;
	int j = 0;
	if(k != 6) {
		while(1) {
			if(!memcmp(data + http_offset + i, "Host: ", 6)) {
				i += 6;
				int length = 0;
				while(1) {
					if(!memcmp(data + http_offset + i, "\r\n", 2)) {
						break;
					}
					captured_host[j] = data[http_offset + i];
					i++;
					j++;
				}
				break;
			}
			i++;
		}
	}
	return;
}
