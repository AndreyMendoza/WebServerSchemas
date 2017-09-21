#include <sys/stat.h>
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
    //s->server.sin_port = htons(5050);
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
    bool deleteHeader = true;
    char fullPath [256];
    memset(fullPath,0,256);
    strcpy(fullPath, s->storage);
    strcat(fullPath, s->fileName);

    //FILE * file2 = fopen("/home/armando/Escritorio/estadio.txt", "w");
    //FILE * file2 = fopen(fullPath, "w");
    //loop para recibir los chunks de datos del servidor

    int tmp_file_fd = get_temporal_file(s->socketDes, fullPath);

    memset(serverReply,0,2000);
    // Obtenemos el encabezado http presente en el archivo temporal
    if(!read(tmp_file_fd, serverReply, 2000)){
        printf("Error al obtener la respuesta a la solicitud\n");
        exit(EXIT_FAILURE);
    }


    // Obtenemos el tamaño total del contenido sin contar el encabezado http
    // y colocamos el puntero donde debe empezar a leer el contenido
    size_t content_length = extract_content_lenght(serverReply);
    lseek(tmp_file_fd, 0L, SEEK_END);
    size_t start_index = get_fd_size(tmp_file_fd) - content_length;
    lseek(tmp_file_fd, start_index, SEEK_SET);

    // Creamos el archivo y guardamos el contenido recibido
    FILE * file = fopen(fullPath, "w");
    copy_content(tmp_file_fd, fileno(file));
    fclose(file);

    printf("Respuesta recibida:\n");
    return true;
}

off_t get_fd_size(int file_fd){

    struct stat st;
    fstat(file_fd, &st);
    return st.st_size;

}

size_t extract_content_lenght(char * buffer){

    char * cpy_buffer = malloc(2000);
    memcpy(cpy_buffer, buffer, 2000);
    strtok(cpy_buffer,"\r\n");
    strtok(0,"\r\n");

    char * content_lenght = malloc(256);
    strcpy(content_lenght, strtok(0, "\r\n"));

    strtok(content_lenght, ":");
    strcpy(content_lenght, strtok(0, " :"));

    return (size_t) strtoll(content_lenght, 0, 10);

}


int get_temporal_file(int from_fd, char * original_file_name){

    char * filename = get_temporal_filename(original_file_name);
    int tmp_file_fd = mkstemp(filename);
    copy_content(from_fd, tmp_file_fd);
    lseek(tmp_file_fd, 0, SEEK_SET);
    unlink(filename);
    return tmp_file_fd;

}

char * get_temporal_filename(char *filepath){

    char * tmp_path = malloc(FILENAME_MAX);
    memset(tmp_path,0,FILENAME_MAX);
    strcat(tmp_path, filepath);
    strcat(tmp_path, ".tmp-XXXXXX");
    return tmp_path;

}

void copy_content(int from_fd, int to_fd){

    char buffer[2000] = {0};
    memset(buffer, 0, 2000);

    ssize_t written_bytes = read(from_fd, buffer, 2000);
    while(written_bytes) {
        write(to_fd, buffer, (size_t) written_bytes);
        written_bytes = read(from_fd, buffer, 2000);
    }

}




/*--------------------------------------------------------------------------------------------------------------------*/

void* RunClient(void * argv)
{
    Server * s =  argv;

    char *message = malloc(100);
    memset(message,0,100);
    strcpy(message,"GET /");
    strcat(message,s->fileName);
    strcat(message, " HTTP/1.1\r\n\r\n");

    //char *message = "GET /satelite.jpg HTTP/1.1\r\n\r\n";
    pthread_t threadID = pthread_self();
    // Indica que se liberaran los recursos al finalizar el procesos del thread
    //pthread_detach(threadID);
    printf("Thread %ld creado!\t, peticion %s", (long) threadID, message);

    char *reply = "";
    printf("\n#------------- Inicializando Cliente -------------#\n\n");

    if (!CreateSocket(s)) { exit(-10); }               // Crear el socket
    if (!Connect(s)) { exit(-20); }
    if (!SendData(s, message)) { exit(-30); };
    if (!ReceiveData(s, reply)) { exit(-40); };
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
