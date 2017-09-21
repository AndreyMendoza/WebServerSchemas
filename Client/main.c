#include "headers/client.h"
#include "headers/List.h"

int main(int argc, char* argv[]) {

    int port = atoi(argv[1]);
    char * storage = argv[2];
    char * files = argv[3];
    char * current_token = strtok(files, ",");
    char * file_node;
    pthread_t request_thread;
    List * tokens = newList();
    List * threads = newList();

    // Se separan los nombres de archivos y se insertan en una lista
    while(current_token){
        addAux(tokens, current_token);
        current_token = strtok(NULL, ",");
    }

    // Se crean todos los hilos para realizar cada solicitud por separado
    while(tokens->size > 0){
        file_node = (char * ) pop(tokens);
        Server *s = malloc(sizeof(Server));
        s->port = port;
        s->storage = storage;
        s->fileName = file_node;

        if(pthread_create(&request_thread, 0, RunClient, s) < 0) {
            printf("No se ha podido solicitar el archivo: %s\n", file_node);
        }
        else{
            add(threads, (void *)(long) request_thread);
        }
    }

    Node * thread_node = threads->head;
    while(thread_node != 0){
        pthread_t pthread = (pthread_t)(long) thread_node->data;
        pthread_join(pthread, 0);
        thread_node = thread_node->next;
    }

    printf("Fin de la consulta de archivos\n");

    return 0;
}