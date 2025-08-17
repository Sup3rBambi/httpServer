#ifndef SERVER
#define SERVER

#include <stddef.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 80

void initServ();
void connectClient();
void sendMsg(const char* msg, size_t lenth);

#endif
