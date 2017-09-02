#include "../headers/server.h"

int RunClient(void)
{

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

    close(socket_desc);
    return 0;
}

char* getHostByName(char* hostname)
{

    char ip[100];
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ((he = gethostbyname(hostname)) == NULL)
    {
        herror("gethostbyname");
        return NULL;
    }

    for (i = 0; addr_list[i] != NULL; i++)
    {
        strcpy(ip, inet_ntoa(*addr_list[i]));
    }

    printf("%s resolved to : %s", hostname, ip);

    return hostname;
}


int RunServer(void)
{

    int socket_desc, newSocket, c, *newSock;
    struct sockaddr_in server, client;
    char *message;

    // Crear socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    // Preparar el sockaddr_en la structura
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8080 );

    // Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("Fallo el binding");
        return 1;
    }
    else
    {
        puts("bind finalizado");
    }


    // Listen
    listen(socket_desc, 3);

    // Accept Connections
    puts("Esperando nuevas solicitudes...");
    c = sizeof(struct sockaddr_in);

    while ( (newSocket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Conexion aceptada");

        // Responder al cliente
        message = "Hola! Recibi tu conexion pero debo irme.\n";
        write(newSocket, message, strlen(message));

        pthread_t snifferThread;
        newSock = malloc(1);
        *newSock = newSocket;


        if( pthread_create( &snifferThread , NULL ,  connectionHandler, (void*) newSock) < 0)
        {
            perror("No fue posible crear el thread");
            return 1;
        }

        puts("Thread creado con exito!");
    }


    if (newSocket < 0)
    {
        puts("Fallo en la conexion.");
        return 1;
    }

    return 0;
}


void *connectionHandler(void *socket_desc)
{
    // Agarrar el socket
    int sock = *(int*)socket_desc;
    int readSize;
    char *message, clientMessage[2000];

    // Enviar mensaje al cliente
    message = "Hola! Soy tu thread de conexion\n";
    write(sock, message, strlen(message));

    message = "Mi deber es comunicarme contigo";
    write(sock, message, strlen(message));

    // Recibir mensaje del cliente
    while ((readSize = recv(sock, clientMessage, 2000, 0)) > 0)
    {
        // Responder al cliente
        write (sock, clientMessage, strlen(message));
    }
    if (readSize == 0)
    {
        puts("El cliente se ha desconectado");
        fflush(stdout);
    }
    else if (readSize == -1)
    {
        perror("Error recibiendo mensaje");
    }


    // Liberar el puntero del socket
    free(socket_desc);

    return 0;
}















