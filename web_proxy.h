#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <resolv.h>
#include <thread>
#include <mutex>
#include <vector>
#include "openssl/ssl.h"
#include "openssl/err.h"
#define FAIL    -1

void str_to_uint16(char* str, uint16_t* ret);
void dump(char *buf);
void client_recv(int fd);
void client_send(int fd);
void web_server_recv();
void web_werver_send();

