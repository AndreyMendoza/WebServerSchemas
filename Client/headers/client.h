#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct Server {
    int socketDes;
    struct sockaddr_in server;
    int port;
    char storage;
    char fileName;
}Server;

bool CreateSocket(Server *s);
bool Connect(Server *s);
bool SendData(Server *s, char *message);
bool ReceiveData(Server *s, char *message);
void RunClient(Server *s);

int RunClients(void);
char* getHostByName(char *hostname);

#endif //CLIENT_CLIENT_H
