#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

//cliente
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


// GetHostByName
#include <netdb.h>


//Otros
#include <stdbool.h>

//Threads
#include <pthread.h>
#include <stdlib.h>


int RunClient(void);
char* getHostByName(char *hostname);
int RunServer(void);
void *connectionHandler(void*);



#endif //SERVER_SERVER_H
