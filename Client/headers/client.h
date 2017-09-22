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
    char *storage;
    char *fileName;
}Server;

bool CreateSocket(Server *s);
bool Connect(Server *s);
bool SendData(Server *s, char *message);
bool ReceiveData(Server *s, char *message);
void * RunClient(void * argv);
int get_temporal_file(int from_fd, char * original_file_name);
char * get_temporal_filename(char *filepath);
void copy_content(int from_fd, int to_fd);
size_t extract_content_lenght(char * buffer);
off_t get_fd_size(int file_fd);

#endif //CLIENT_CLIENT_H
