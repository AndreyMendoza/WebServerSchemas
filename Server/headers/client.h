#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include "../headers/structs.h"


bool CreateSocket(Server *s);
bool Connect(Server *s, int port);
bool SendData(Server *s, char *message);
bool ReceiveData(Server *s, char *message);
void RunClient(Server *s, char * argv[]);

int RunClients(void);
char* getHostByName(char *hostname);


#endif //SERVER_CLIENT_H

