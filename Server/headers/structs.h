//
// Created by armando on 19/09/17.
//

#ifndef SERVER_STRUCTS_H
#define SERVER_STRUCTS_H

#include <netdb.h>

typedef struct Server {
    int socketDes;
    struct sockaddr_in server;
}Server;

#endif //SERVER_STRUCTS_H
