#include "headers/server.h"

int main() {

    int socket_desc;
    struct sockaddr_in server;
    char *message, serverReply[2000];

    //  Crear Socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("No se pudo crear el socket");
    }

    server.sin_addr.s_addr = inet_addr("172.217.8.78");
    server.sin_family = AF_INET;
    server.sin_port = htons( 80 );

    //Conectarse a un servidor remoto
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("Error de conexion");
        return 1;
    }

    puts("Conectado");


    // Enviar datos
    message = "GET / HTTP/1.1\r\n\r\n";
    if (send(socket_desc, message, strlen(message), 0) < 0)
    {
        puts("Error enviando datos.");
        return 1;
    }
    puts("Datos enviados.\n");


    // Recibiendo respuesta del servidor.
    if (recv(socket_desc, serverReply, 2000, 0) < 0)
    {
        puts("Error recibiendo datos.");
    }
    puts("Respuesta recibida\n");
    puts(serverReply);

    return 0;

}