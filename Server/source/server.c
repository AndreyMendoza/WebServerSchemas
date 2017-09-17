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

bool BindSocket(Server *s, char *ip, int port)
{
    printf("Asignando direccion IP y puerto...");

    // Asignar IP
    struct in_addr ipAddr;
    if (inet_pton(AF_INET, &ip, &ipAddr) == -1)
    {
        printf("FAILED\n");
        return false;
    }

    // Preparar el sockaddr_en la structura
    s->server.sin_family = AF_INET;
    //s->server.sin_addr.s_addr = INADDR_ANY;
    s->server.sin_addr = ipAddr;
    s->server.sin_port = htons( (uint16_t) port);

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
    int c, newSocket;


    printf("Esperando nuevas solicitudes...\n");
    c = sizeof(struct sockaddr_in);

    while ( (newSocket = accept(s->socketDes, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {

        // Crear Thread que se dedique a esa solicitud
        if (serverType == 3)
            CreateThread(newSocket);

    }


    if (newSocket < 0)
    {
        puts("Fallo en la conexion.");

    }
}

/*--------------------------------------------------------------------------------------------------------------------*/

void RunServer(struct Server *s, int port)
{
    // Ejecuta un servidor y lo deja esperando solicitudes.

    printf("\n#------------- Inicializando Server -------------#\n\n");

    if (!CreateSocket(s)) { return; }               // Crear el socket
    if (!BindSocket(s, "127.0.0.1", port)) { return; }           // Bindear el socket a la direccion y puerto
    if (!ListenSocket(s)) { return; }               // Establecer en modo de espera
    printf("\n#----------- Configuracion Finalizada -------------#\n\n");
    AcceptMode(s, 3);                               // Aceptar solicitudes de cierto modo(revisar los modos en el metodo)

}

/*--------------------------------------------------------------------------------------------------------------------*/

void CreateThread(int newSocket)
{
    int *newSock;

    printf("Conexion aceptada.\n");

    pthread_t snifferThread;
    newSock = malloc(1);
    *newSock = newSocket;


    if (pthread_create(&snifferThread, NULL, connectionHandler, (void *) newSock) < 0) {
        perror("No fue posible crear el thread");

    }
    printf("Thread creado con exito!\n");
}

/*--------------------------------------------------------------------------------------------------------------------*/

bool send_all(int socket, void *buffer, size_t length)
{
    char *ptr = (char*) buffer;
    while (length > 0)
    {
        int i = send(socket, ptr, length,0);
        if (i < 1) return false;
        ptr += i;
        length -= i;
    }
    return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/

bool writeStrToClient(int sckt, const char *str)
{
    return send_all(sckt, str, strlen(str));
}

/*--------------------------------------------------------------------------------------------------------------------*/

int prueba(int client){

    long fsize;
    //FILE *fp = fopen("../tests/test1.html", "rb");
    //FILE *fp = fopen("../tests/test2.txt", "rb");
    //FILE *fp = fopen("../tests/test3.png", "rb");
    //FILE *fp = fopen("../tests/test4.jpg", "rb");
    FILE *fp = fopen("../tests/satelite.jpg", "rb");
    if (!fp){
        perror("The file was not opened");
        exit(1);
    }

    printf("The file was opened\n");

    if (fseek(fp, 0, SEEK_END) == -1){
        perror("The file was not seeked");
        exit(1);
    }

    fsize = ftell(fp);
    if (fsize == -1) {
        perror("The file size was not retrieved");
        exit(1);
    }
    rewind(fp);

    char *msg = (char*) malloc(fsize);
    if (!msg){
        perror("The file buffer was not allocated\n");
        exit(1);
    }

    if (fread(msg, fsize, 1, fp) != 1){
        perror("The file was not read\n");
        exit(1);
    }
    fclose(fp);

    if (!writeStrToClient(client, "HTTP/1.1 200 OK\r\n")){
        close(client);
    }

    //if (!writeStrToClient(client, "Content-Type: text/html\r\n")){
    //if (!writeStrToClient(client, "Content-Type: text/plain\r\n")){
    //if (!writeStrToClient(client, "Content-Type: image/png\r\n")){
    if (!writeStrToClient(client, "Content-Type: image/jpg\r\n")){
        close(client);
    }

    if (!writeStrToClient(client, "Connection: close\r\n\r\n") == -1){
        close(client);
    }

    //if (!writeStrToClient(client, "<html><body><H1>Hello world Armando2232 jajajja</H1></body></html>")){
    if (!send_all(client, msg, fsize)){
        close(client);
    }

    printf("The file was sent successfully\n");
}

/*--------------------------------------------------------------------------------------------------------------------*/

void *connectionHandler(void *socket_desc)
{
    // Agarrar el socket
    int client = *(int*)socket_desc;

    ssize_t readSize;
    char *message, clientMessage[2000];
    memset(clientMessage, 0, 2000);

    readSize = recv(client, clientMessage, 2000, 0);

    // Responder al cliente
    printf("Mensaje Recibido:\n");
    printf(clientMessage);

    prueba(client);


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
    close(client);

    return 0;
}















