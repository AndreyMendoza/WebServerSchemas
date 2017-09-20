#include "../headers/client.h"

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

bool Connect(Server *s)
{
    printf("Connectandose al servidor...");

    // Preparar el sockaddr_en la structura
    s->server.sin_family = AF_INET;
    //s->server.sin_addr.s_addr = inet_addr("74.125.141.104");
    //s->server.sin_port = htons( 80 );
    s->server.sin_addr.s_addr = inet_addr("127.0.0.1");
    s->server.sin_port = htons(s->port);
    if (connect(s->socketDes, (struct sockaddr *)&s->server, sizeof(s->server)) < 0)
    {
        puts("FAILED\n");
        return false;
    }

    puts("OK\n");
    return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/

bool SendData(Server *s, char *message)
{
    // Enviar datos al servidor
    printf("Enviando:\n\t");
    puts(message);

    if (send(s->socketDes, message, strlen(message), 0) < 0)
    {
        puts("ERROR: No fue posible enviar los datos.");
        return false;
    }
    puts("Datos enviados con EXITO!.\n");
    return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/

bool ReceiveData(Server *s, char *messageReply)
{
    // Recibiendo respuesta del servidor.
    char serverReply[2000];
    printf("Recibiendo respuesta del servidor...");

    int size_recv , total_size= 0;
    //char * buffer[8000] = {0};
    //memset(buffer,0,8000);
    //bool deleteHeader = true;
    char * fullPath = strcat(s->storage,s->fileName);
    //FILE * file2 = fopen("/home/armando/Escritorio/testArmando.html", "w");
    FILE * file2 = fopen(fullPath, "w");

    //loop para recibir los chunks de datos del servidor
    while(1)
    {
        memset(serverReply ,0 , 2000); //Se limpia el buffer
        if((size_recv =  recv(s->socketDes , serverReply , 2000 , 0) ) <= 0)
        {
            break;
        }
        else
        {
            total_size += size_recv;
            //printf("%s" , serverReply);

            //strcat(buffer,serverReply);

            fprintf(file2,serverReply);
        }
    }

    fclose(file2);

    printf("Respuesta recibida:\n");
    //puts(buffer);
    return true;
}



/*--------------------------------------------------------------------------------------------------------------------*/

void RunClient(Server *s)
{
    //char *message = "GET /test1.html HTTP/1.1\r\n\r\n";
    char *message[100];
    memset(message,0,100);
    strcpy(message,"GET /");
    strcat(message,s->fileName);
    strcat(message, " HTTP/1.1\r\n\r\n");
    char *reply = "";
    printf("\n#------------- Inicializando Cliente -------------#\n\n");

    if (!CreateSocket(s)) { return; }               // Crear el socket
    if (!Connect(s)) { return; }
    if (!SendData(s, message)) { return; };
    if (!ReceiveData(s, reply)) { return; };
    puts("Informacion recibida con extio!");

    close(s->socketDes);
}

/*--------------------------------------------------------------------------------------------------------------------*/

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
