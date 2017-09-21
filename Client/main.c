#include "headers/client.h"
#include "headers/List.h"

//int main(int argc, char* argv[]) {
int main() {

    /*int port = atoi(argv[1]);
    char * storage = argv[2];
    char * files = argv[3];
     */
    int port = 5050;
    char * storage = "/home/armando/Escritorio/";
    char files[2000] = "test1.html,test2.txt,estadio.jpg,satelite.jpg,test3.png";

    List * tokens = newList();
    char * current_token = strtok(files, ",");
    while(current_token){
        add(tokens, current_token);
        current_token = strtok(NULL, ",");
    }


    List * threads = newList();


    // Se crean todos los hilos para realizar las solicitudes
    pthread_t request_thread;
    //Node * file_node = tokens->head;
    char * file_node;

    //while(file_node != 0){
    while(tokens->size > 0){
        file_node = (char * ) pop(tokens);
        Server *s = malloc(sizeof(Server));// = {NULL, NULL, port, storage, file_node->data};
        s->port = port;
        s->storage = storage;
        //s.fileName = file_node->data;
        s->fileName = file_node;
        //if (!CreateSocket(&s)) { return -30; }               // Crear el socket
        //if (!Connect(&s)) { return -31; }

        if(pthread_create(&request_thread, 0, RunClient, s) < 0) {
            //printf("No se ha podido solicitar el archivo: %s\n", file_node->data);
            printf("No se ha podido solicitar el archivo: %s\n", file_node);
        }
        else{
            add(threads, (void *)(long) request_thread);
        }

        //file_node = file_node->next;
    }

    Node * thread_node = threads->head;
    while(thread_node != 0){
        pthread_t pthread = (pthread_t)(long) thread_node->data;
        pthread_join(pthread, 0);
        thread_node = thread_node->next;
    }

    printf("Fin de la consulta de archivos\n");

    /*Server s;
    s.fileName = "satelite.jpg";
    s.port = 5050;
    s.storage = "/home/armando/Escritorio/";
    RunClient(&s);

    Server s2;
    s2.fileName = "estadio.jpg";
    s2.port = 5050;
    s2.storage = "/home/armando/Escritorio/";
    RunClient(&s2);*/
    return 0;
}