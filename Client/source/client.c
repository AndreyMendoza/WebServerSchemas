#include "../headers/client.h"
#include "../headers/List.h"
#include <pwd.h>
#include <sys/stat.h>

/**
 * Función que copia el contenido de un stream a otro stream
 * por medio de chuncks (fragmentos). Puede ser de un archivo
 * a otro, de socket a socket, de socket a archivo o viceversa
 * @param from_fd: Descriptor de donde vienen los datos
 * @param to_fd: Descriptor para donde se copian los datos
 * @return
 */
void copy_content(int from_fd, int to_fd);

/**
 * Determina si un nombre es válido con base a un conjunto
 * de carácteres que se consideren invalidos
 * @param name: Nombre que se desea validar
 * @param bad_chars: Carácteres invalidos
 * @return 1 si es nombre es válido, 0 sino
 */
int is_valid_name(char * name, char bad_chars[]);

/**
 * Determina si el nombre de un archivo es válido por medio
 * de la función is_valid_name(2) y los caracteres !@%^*~|
 * @param filename: Nombre del archivo que se desea validar
 * @return 1 si es nombre es válido, 0 sino.
 */
int is_valid_filename(char * filename);

/**
 * Determina si el nombre de un archivo es válido por medio
 * de la función is_valid_name(2) y los caracteres !@%^*~|\#.
 * @param filename: Nombre del archivo que se desea validar
 * @return 1 si es nombre es válido, 0 sino.
 */
int is_valid_folder(char * foldername);

/**
 * Obtiene la dirección de la carpeta del usuario que este en
 * sesión. Por ejemplo: /home/julian/
 * @return ruta de la carpeta home del usuario
 */
char * get_homedir();

/**
 * Concatena la dirección home con la del folder que se
 * especifique. Si ya la posee no realiza ninguna acción
 * Ejemplo: /home/julian/ * /folder/test/ = /home/julian/folder/test/
 * @return concatenación de homedir con folderpath
 */
char * map_folderpath_to_homedir(char * folderpath);

/**
 * Crear una carpeta con el nombre especificado
 * @param foldername: ruta absoluta del folder
 * @return 1 si se creó, 0 sino.
 */
int mkdir_folder(char * foldername);

/**
 * Concatena el nombre del folder con un nombre de archivo
 * para asi obtener la ruta absoluta de dicho archivo
 * @return ruta absoluta del archivo
 */
char * get_absolute_filename(char * base_folder, char *filename);

/**
 * Con base a una ruta absoluta de un archivo, crea un nombre
 * único para un archivo temporal.
 * Ejemplo: get_temporal_filename("/home/test1.txt) -> /home/test1.txt.tmp-456fer
 * @return ruta absoluta del archivo
 */
char * get_temporal_filename(char * filepath);

/**
 * Separa una cadena en varios tokens
 * @param string: cadena a separar
 * @param delim: delimitador
 * @return List con punteros a los tokens
 */
void * tokenizer(char * string, char * delim);

/**
 * Dado un archivo descriptor, retorna el tamaño del contenido
 * @param file_fd: archivo descriptor del stream
 * @return off_t que representa el tamaño del contenido
 */
off_t get_fd_size(int file_fd);

/**
 * Ejecuta una función del sistema para abrir el archivo
 * con el programa predeterminado según el usuario en sesión
 * @param filename: Nombre del archivo para abrir
 */
void show_file(char * filename);


int get_temporal_file(int from_fd, char * original_file_name);

size_t extract_content_lenght(char * buffer);;


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
    s->server.sin_port = htons(5050);
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
    /*if (recv(s->socketDes, serverReply, 2000, 0) < 0)
    {
        puts("FAILED\n");
        return false;
    }*/

    int size_recv , total_size= 0;
    char * buffer[8000] = {0};
    memset(buffer,0,8000);


    FILE * file2 = fopen("/home/armando/Escritorio/testArmando.txt", "w");

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
            strcat(buffer,serverReply);


            // Puntero al primero token
            fprintf(file2,serverReply);
        }
    }

    fclose(file2);

    int client_fd = s->socketDes;
    char * filename;
    char * storage_folder = "/home/armando/Escritorio/";

    filename = "/home/armando/Escritorio/test4.txt";//get_absolute_filename(storage_folder, filename);

    // Creamos un archivo temporal con la información leída del socket.
    int tmp_file_fd = get_temporal_file(s->socketDes, filename);

    /*FILE * file2 = fopen(filename, "w");
    fprintf(file2,buffer);
    fclose(file2);
     */

    // Obtenemos el tamaño total del contenido sin contar el encabezado http
    // y colocamos el puntero donde debe empezar a leer el contenido
    size_t content_length = size_recv;
    lseek(tmp_file_fd, 0, SEEK_END);
    size_t start_index = get_fd_size(tmp_file_fd) - content_length;
    lseek(tmp_file_fd, start_index, SEEK_SET);


    // Creamos el archivo y guardamos el contenido recibido
    //FILE * file = fopen(filename, "w");
    //copy_content(tmp_file_fd, fileno(file));
    //fclose(file);

    // Cerramos el socket y mostramos el archivo resultante
    close(s->socketDes);
    //show_file(filename);

    printf("Respuesta recibida:\n");
    puts(buffer);
    return true;
}



/*--------------------------------------------------------------------------------------------------------------------*/

void RunClient(Server *s)
{
    char *message = "GET /test4.jpg HTTP/1.1\r\n\r\n";
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
