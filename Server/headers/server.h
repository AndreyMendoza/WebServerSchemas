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
#include <sys/syscall.h>
#include "../headers/List.h"

typedef struct Server {
    int socketDes;
    struct sockaddr_in server;
}Server;


pthread_t threadID;
pthread_mutex_t lock;
List *clients;


bool CreateSocket(Server *s);
bool BindSocket(Server *s, char *ip, int port);
bool ListenSocket(Server *s);
void AcceptMode(Server *s, int serverType, int nThreads);
void RunServer(Server *s, int port, int type, int nThreads);

void *ThreadedServer(void *clientSock);
void CreateThread(int newSocket);
char *GetFileName(char *header);
bool SendAll(int socket, void *buffer, size_t length);
bool WriteToClient(int sckt, const char *str);
void ProcessRequest(int client, char *fileName);
bool InitThreadPool(int nThreads);
void *PreThreadedServer(void*);
void FIFOServer(int client);



#endif //SERVER_SERVER_H
