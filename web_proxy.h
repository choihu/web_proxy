#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <resolv.h>
#include <netdb.h>
#include <thread>
#include <mutex>
#include <vector>

#define TCP_PORT 80
using namespace std;

extern mutex m;
extern vector<pair<char*, int>> sk;

//declaration
//client: client who want to use proxy
//web: web server that client want to connect

int setup_socket(uint16_t port, uint32_t ip_addr);
void str_to_uint16(char* str, uint16_t* ret);
void str_to_uint32(char* str, uint32_t* ret);
void dump(char *buf);
void client_to_web(int fd);
void web_to_client(int fd);
void host_check(char *data, char *captured_host);

