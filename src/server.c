#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int socket_id = 0;
int client_id = 0;

void initServ() {
    printf("Starting HTTP Server\n");

    socket_id = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socket_id, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("Error while binding the socket");
        return;
    }

    printf("Initiation completed\n");
}

void connectClient() {
    printf("Waiting for client to connect\n");

    while (listen(socket_id, 1) < 0);
    client_id = accept(socket_id, NULL, NULL);

    printf("Client connected\n");

    sendHomePage();
}

void sendHomePage() {
    char* homePage = readFile("pages/index.html");
    if (homePage == NULL) {
        printf("index.html not found\n");
        sendMsg("page not found");
        return;
    }
    sendHtml(homePage);
    free(homePage);
}

char* readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    unsigned long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* content = (char*)malloc(sizeof(char) * size);
    fread(content, sizeof(char), size, file);
    fclose(file);
    return content;
}

void sendMsg(const char *msg) {
    send(client_id, msg, strlen(msg), 0);
}

void sendHtml(const char* body) {
    const char* header = "HTTP/1.1 200 Ok\r\nContent-Type: text/html\r\n\r\n";

    unsigned long msgLen = strlen(body) + strlen(header) + 1;
    char* msg = (char*)malloc(msgLen);
    strcpy(msg, header);
    strcat(msg, body);

    size_t length = msgLen;
    send(client_id, msg, length, 0);

    free(msg);
}
