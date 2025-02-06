#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <curses.h>
#include <pthread.h>


int createTCPIpv4Socket();
struct sockaddr_in* createIpv4Address(char* ip, int port);
