#include "../headers/server.h"


/*--------------------------------------------------------------------------------------------------------------------*/

bool CreateSocket(Server *s)
{
    // Crea el socket para un servidor.
    printf("Creando Socket...");
    s->socketDes = socket(AF_INET, SOCK_STREAM, 0);

    if (s->socketDes == -1) {
        printf("FAILED\n");
        return false;
    }
    printf("OK\n");
    return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/

bool BindSocket(Server *s)
{
    printf("Asignando direccion IP y puerto...");

    // Preparar el sockaddr_en la structura
    s->server.sin_family = AF_INET;
    s->server.sin_addr.s_addr = INADDR_ANY;
    s->server.sin_port = htons( 8080 );

    if( bind(s->socketDes, (struct sockaddr *)&s->server, sizeof(s->server)) < 0)
    {
        printf("FAILED\n");
        return false;
    }
    printf("OK\n");
    return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/

bool ListenSocket(struct Server *s)
{
    printf("Estableciendo en modo de espera...");
    if (listen(s->socketDes, 1) == -1)
    {
        printf("FAILED\n");
        return false;
    }
    printf("OK\n");
    return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void AcceptMode(Server *s, int serverType)
{
    /*-----------------------------------  Server Types ------------------------------------/*
     *
     * 1 - FIFO: se atendenderan la solicitudes conforme van llegando.
     * 2 - FORK: se crea un PROCESO para cada solicitud.
     * 3 - THREAD: se crea un THREAD para cada solicitud.
     * 4 - PRE-THREAD: a una solicitud se le ASIGNA un thread que esta creado previamente.
     *
     *--------------------------------------------------------------------------------------*/

    struct sockaddr_in client;
    int c, newSocket, *newSock;


    printf("Esperando nuevas solicitudes...\n");
    c = sizeof(struct sockaddr_in);

    while ( (newSocket = accept(s->socketDes, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        printf("Conexion aceptada.");

        pthread_t snifferThread;
        newSock = malloc(1);
        *newSock = newSocket;


        if( pthread_create( &snifferThread , NULL ,  connectionHandler, (void*) newSock) < 0)
        {
            perror("No fue posible crear el thread");

        }

        printf("Thread creado con exito!\n");
    }


    if (newSocket < 0)
    {
        puts("Fallo en la conexion.");

    }
}

/*--------------------------------------------------------------------------------------------------------------------*/

void RunServer(struct Server *s)
{
    // Ejecuta un servidor y lo deja esperando solicitudes.

    printf("\n#------------- Inicializando Server -------------#\n\n");

    if (!CreateSocket(s)) { return; }               // Crear el socket
    if (!BindSocket(s)) { return; }                 // Bindear el socket a la direccion y puerto
    if (!ListenSocket(s)) { return; }               // Establecer en modo de espera
    AcceptMode(s, 3);                               // Aceptar solicitudes de cierto modo(revisar los modos en el metodo)

    printf("\n#----------- Configuracion Finalizada -------------#\n\n");
}

/*--------------------------------------------------------------------------------------------------------------------*/

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















