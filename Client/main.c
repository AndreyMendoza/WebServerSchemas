#include "headers/client.h"
#include "headers/List.h"

//int main(int argc, char* argv[]) {
int main() {

    /*int port = atoi(argv[1]);
    char * storage = argv[2];
    char * files = argv[3];
     */
    /*int port = 5050;
    char * storage = "/home/armando/escritorio/";
    char files[2000] = "test1.html,test2.txt";

    //char * filesAux = malloc(strlen(files));
    //strcpy(filesAux,files);

    List * tokens = newList();
    char * current_token = strtok(files, ",");
    while(current_token){
        add(tokens, current_token);
        current_token = strtok(NULL, ",");
    }

    //add(tokens,"test1.html");
    //add(tokens,"test2.txt");


    List * threads = newList();

    // Se crean todos los hilos para realizar las solicitudes
    Node * file_node = tokens->head;
    while(file_node != 0){

        pthread_t request_thread;
        Server s = {NULL, NULL, port, storage, file_node->data};
        s.port = port;
        s.storage = storage;
        s.fileName = file_node->data;

        if(pthread_create(&request_thread, NULL, RunClient, &s) < 0) {
            printf("No se ha podido solicitar el archivo: %s\n", file_node->data);
        }
        else{
            add(threads, (void *)(long) request_thread);
        }

        file_node = file_node->next;
    }

    Node * thread_node = threads->head;
    while(thread_node != 0){
        pthread_t pthread = (pthread_t)(long) thread_node->data;
        pthread_join(pthread, 0);
        thread_node = thread_node->next;
    }

    printf("Fin de la consulta de archivos\n");*/
    Server s = {NULL, NULL, 5050, "/home/armando/Escritorio", "test1.html"};
    RunClient(&s);
    return 0;
}