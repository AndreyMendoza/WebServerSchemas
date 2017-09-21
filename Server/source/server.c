#include "../headers/server.h"
#include <wait.h>
#include <sys/types.h>

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

void AcceptMode(Server *s, int serverType, int nThreads)
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
    int c, newClient;


    printf("Esperando nuevas solicitudes...\n");
    c = sizeof(struct sockaddr_in);

    while ( (newClient = accept(s->socketDes, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        // Atender solicitud obtenida
        if (serverType == 1)
        {
            FIFOServer(newClient);
        }
        // Crear Proceso que se dedique a esa solicitud
        else if (serverType == 2) {
            CreateProcess(newClient, s, serverType);
        }

        // Crear Thread que se dedique a esa solicitud
        else if (serverType == 3) {
            CreateThread(newClient);
        }
        // Servidor modo PreThreaded
        else if (serverType == 4)
        {
            // Bloquear la lista para leerla
            pthread_mutex_lock(&lock);

            // Agregar cliente a la lista de clientes pendientes
            add(clients, &newClient);

            pthread_mutex_unlock(&lock);
        }

    }


    if (newClient < 0)
    {
        puts("Fallo en la conexion.");

    }
}

/*--------------------------------------------------------------------------------------------------------------------*/

void RunServer(struct Server *s, int port, int type, int nThreads)
{
    /*-----------------------------------  Server Types ------------------------------------/*
     *
     * 1 - FIFO: se atendenderan la solicitudes conforme van llegando.
     * 2 - FORK: se crea un PROCESO para cada solicitud.
     * 3 - THREAD: se crea un THREAD para cada solicitud.
     * 4 - PRE-THREAD: a una solicitud se le ASIGNA un thread que esta creado previamente.
     *
     *--------------------------------------------------------------------------------------*/

    // Ejecuta un servidor y lo deja esperando solicitudes.

    printf("\n#------------- Inicializando Server -------------#\n\n");

    // Crear el socket
    if (!CreateSocket(s)) { return; }

    // Bindear el socket a la direccion y puerto
    if (!BindSocket(s, "127.0.0.1", port)) { return; }

    // Establecer en modo de espera
    if (!ListenSocket(s)) { return; }

    printf("\n#----------- Configuracion Finalizada -------------#\n\n");

    // Aceptar solicitudes de cierto modo(revisar los modos en el metodo)

    // Se inicializan los threads necesarios
    if (type == 4)
    {
        if(!InitThreadPool(nThreads))
            return;
    }
    AcceptMode(s, type, nThreads);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void FIFOServer(int client)
{
    ssize_t readSize;
    char *message, clientMessage[2000], *fileName;
    memset(clientMessage, 0, 2000);
    // Lectura de la solicitud
    readSize = recv(client, clientMessage, 2000, 0);
    printf(clientMessage);
    // Archivo solicitado por el cliente
    fileName = GetFileName(clientMessage);

    ProcessRequest(client, fileName);

    if (readSize == 0)
    {
        printf("Thread %ld liberado. El cliente se ha desconectado%d\n",(long)threadID, client);
        fflush(stdout);
    }
    else if (readSize == -1)
    {
        perror("Error recibiendo mensaje del cliente.");
    }
    // Liberar el puntero del socket
    close(client);

}

/*--------------------------------------------------------------------------------------------------------------------*/
void CreateProcess(int newSocket, Server *s, int serverType)
{
    int *newSock;

    printf("Conexion de Fork aceptada.\n");

    newSock = malloc(1);
    *newSock = newSocket;

    /* Identificador del proceso creado */
    pid_t idProceso;

    /* Se crea el proceso hijo. En algún sitio dentro del fork(), nuestro
     * programa se duplica en dos procesos. Cada proceso obtendrá una salida
     * distinta. */
    idProceso = fork();

    /* Si fork() devuelve -1, es que hay un error y no se ha podido crear el
     * proceso hijo. */
    if (idProceso == -1)
    {
        perror ("No se pudo crear el proceso");
        exit (-1);
    }

    /* fork() devuelve 0 al proceso hijo.*/
    if (idProceso == 0)
    {
        /* El hijo escribe su pid en pantalla y el valor de variable */
        printf ("Proceso Hijo  : Mi pid es %d. El pid de mi padre es %d\n",
                getpid(), getppid());

        ThreadedServer((void *) newSock);

        exit(33);
    }

    /* fork() devuelve un número positivo al padre. Este número es el id del
     * hijo. */
    if (idProceso > 0)
    {
        /* El proceso padre escribe su pid y el de su hijo */
        printf ("Proceso Padre : Mi pid es %d. El pid de mi hijo es %d\n",
                getpid(), idProceso);
        close(newSocket);
        //El num de threads es 0 pues no se va usar
        AcceptMode(s, serverType,0);
    }
}

bool InitThreadPool(int nThreads)
{
    int i;
    printf("Iniciando conjunto de threads...");

    clients = newList();

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("FAILED\n");
        return false;
    }

    for (i = 0; i < nThreads; i++)
    {
        if (pthread_create(&threadID, NULL, PreThreadedServer, NULL) != 0)
        {
            printf("FAILED\n");
            break;
        }
    }

    printf("OK\n");
    return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void *PreThreadedServer(void *null)
{
    int client;
    ssize_t readSize;
    char *message, clientMessage[2000], *fileName;
    pthread_t threadID = pthread_self();

    // Indica que se liberaran los recursos al finalizar el procesos del thread
    pthread_detach(threadID);


    printf("Thread %ld creado!\n", (long) threadID);

    // Bloquear la lista para leerla

    while (1) {
        pthread_mutex_lock(&lock);

        if (peek(clients) != NULL)
            client = *(int*)pop(clients);
        else
            client = NULL;

        pthread_mutex_unlock(&lock);

        if (client != NULL)
        {
            printf("Thread %ld procesando el cliente %d\n",(long)threadID, client);

            memset(clientMessage, 0, 2000);
            // Lectura de la solicitud
            readSize = recv(client, clientMessage, 2000, 0);

            // Archivo solicitado por el cliente
            fileName = GetFileName(clientMessage);

            ProcessRequest(client, fileName);

            if (readSize == 0)
            {
                printf("Thread %ld liberado. El cliente se ha desconectado%d\n",(long)threadID, client);
                fflush(stdout);
            }
            else if (readSize == -1)
            {
                perror("Error recibiendo mensaje del cliente.");
            }
            // Liberar el puntero del socket
            close(client);
        }
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/

void CreateThread(int newSocket)
{
    int *newSock;

    printf("Conexion aceptada.\n");

    pthread_t snifferThread;
    newSock = malloc(1);
    *newSock = newSocket;


    if (pthread_create(&snifferThread, NULL, ThreadedServer, (void *) newSock) < 0) {
        perror("No fue posible crear el thread");

    }
    printf("Thread creado con exito!\n");
}

/*--------------------------------------------------------------------------------------------------------------------*/

void *ThreadedServer(void *clientSock)
{
    // Agarrar el socket
    int client = *(int*)clientSock;

    ssize_t readSize;
    char *message, clientMessage[2000];
    memset(clientMessage, 0, 2000);

    // Lectura de la solicitud
    readSize = recv(client, clientMessage, 2000, 0);

    // Archivo solicitado por el cliente
    char *fileName = GetFileName(clientMessage);

    ProcessRequest(client, fileName);

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
    printf("Liberando socket");
    close(client);

    return 0;
}

/*--------------------------------------------------------------------------------------------------------------------*/

char *GetFileName(char *header)
{
    char *fileName;

    // Puntero al primero token
    fileName = strtok(header, " ");
    fileName = strtok(NULL, " ");

    return fileName;

}

/*--------------------------------------------------------------------------------------------------------------------*/

char *GetContentType(char *fileName)
{
    char *extension, *fileType, *result;

    extension = strtok(fileName, ".");
    extension = strtok(NULL, ".");

    if (strcmp(extension, "jpg") == 0 || strcmp(extension, "png") == 0)
        fileType = "Content-Type: image/";
    else if (strcmp(extension, "html") == 0)
    {
        fileType = "Content-Type: text/";
        extension = "html";
    }
    else
    {
        fileType = "Content-Type: text/";
        extension = "plain";
    }

    result = malloc(strlen(fileType) + 15);
    strcpy(result, fileType);
    strcat(result, extension);
    strcat(result, "\r\n");

    return result;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void ProcessRequest(int client, char *fileName){

    size_t fsize;
    char *path, *filePath, *msg, *contentType;

    // Formando ruta relativa del archivo por enviar
    path = "../tests";
    filePath = malloc(strlen(path) + 5);
    strcpy(filePath, path);
    strcat(filePath, fileName);

    // Abrir archivo por enviar
    FILE *fp = fopen(filePath, "rb");
    bool fileNotFound = false;
    // Si el archivo no se encuentra, enviar HTML de "no encontrado"
    if (!fp) {
        perror("Archivo no encontrado");
        fp = fopen("../errors/notfound.html", "rb");
        fileNotFound = true;
    }

    // Verificar que el archivo contenga informacion
    fseek(fp, 0, SEEK_END);
    fsize = (size_t) ftell(fp);
    rewind(fp);

    // Lectura del archivo
    msg = (char*) malloc(fsize);
    fread(msg, fsize, 1, fp);
    fclose(fp);

    // Construir encabezado
    WriteToClient(client, "HTTP/1.1 200 OK\r\n");
    if(fileNotFound){
        contentType = "Content-Type: text/html\r\n";
    }else{
        contentType = GetContentType(fileName);
    }

    WriteToClient(client, contentType);
    char largo[256];
    sprintf(largo,"Content-Length: %zu \r\n\r\n",fsize);

    //strcpy(largo,"Content-Length: ");
    //strcat(largo,(fsize));
    WriteToClient(client, largo);

    // Envio del archivo al cliente
    SendAll(client, msg, fsize);

    printf("Respuesta enviada al cliente!\n");
}

/*--------------------------------------------------------------------------------------------------------------------*/

bool SendAll(int socket, void *buffer, size_t length)
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

bool WriteToClient(int sckt, const char *str)
{
    return SendAll(sckt, str, strlen(str));
}

/*--------------------------------------------------------------------------------------------------------------------*/








