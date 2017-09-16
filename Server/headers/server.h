#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

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
}Server;

bool CreateSocket(Server *s);
bool BindSocket(Server *s, char *ip, int port);
bool ListenSocket(Server *s);
void AcceptMode(Server *s, int serverType);
void RunServer(Server *s, int port);

void *connectionHandler(void*);
void CreateThread(int newSocket);



#endif //SERVER_SERVER_H
