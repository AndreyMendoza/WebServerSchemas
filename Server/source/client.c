#include "../headers/client.h"


/*--------------------------------------------------------------------------------------------------------------------*/

bool Connect(Server *s)
{
    printf("Connectandose al servidor...");

    // Preparar el sockaddr_en la estructura
    s->server.sin_family = AF_INET;
    s->server.sin_addr.s_addr = inet_addr("74.125.141.104");
    s->server.sin_port = htons(80);

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
    if (recv(s->socketDes, serverReply, 2000, 0) < 0)
    {
        puts("FAILED\n");
        return false;
    }
    printf("Respuesta recibida\n");
    puts(serverReply);
    return true;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void RunClient(Server *s)
{
    char *message = "GET / HTTP/1.1\r\n\r\n";
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



