#include "server.h"

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
    connectClient();
}

void connectClient() {
    printf("Waiting for client to connect\n");

    while (listen(socket_id, 1) < 0);
    client_id = accept(socket_id, NULL, NULL);

    printf("Client connected\n");

    char msg[] = "Hello world! from the server";
    sendMsg(msg, sizeof(msg));
}

void sendMsg(const char* msg, size_t length) {
    send(client_id, msg, length, 0);
}
