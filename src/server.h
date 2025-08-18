#ifndef SERVER
#define SERVER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 80

void initServ();
void connectClient();
void sendHomePage();
char* readFile(const char* filename);
void sendMsg(const char* msg);

#endif
