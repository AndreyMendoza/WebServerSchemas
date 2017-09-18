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

void *ThreadedServer(void *clientSock);
void CreateThread(int newSocket);
char *GetFileName(char *header);
bool SendAll(int socket, void *buffer, size_t length);
bool WriteToClient(int sckt, const char *str);
void ProcessRequest(int client, char *fileName);



#endif //SERVER_SERVER_H
