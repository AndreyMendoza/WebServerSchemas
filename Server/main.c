#include "headers/server.h"

int main(int argc, char *argv[]) {
    //./Server fi 5050
    //Se toma el modo de ejecucion
    char * ExecType = argv[1];

    //Declaracion del servidor a utilizar
    Server *server = {NULL, NULL};

    //Se determina el tipo de ejecucion
    /* fi = FIFO
     * fo = Fork
     * th = Thread
     * pt = Pre-Thread
     * */

    /*RunServer(Server, port, type, nThreads)*/
    int port, type, numThreads;

    if (strcmp(ExecType, "fi") == 0){
        type = 1;
        numThreads = 1;
    }
    else if (strcmp(ExecType, "fo") == 0) {
        type = 2;
        numThreads = 1;
    }
    else if (strcmp(ExecType, "th") == 0) {
        type = 3;
        numThreads = 1;
    }
    else if (strcmp(ExecType, "pt") == 0) {
        type = 4;
        numThreads = atoi(argv[3]);
        printf("Num de Threads %d\n",numThreads);
    }
    else {
        printf("Tipo de ejecucion %s desconocida\n", ExecType);
        exit(-1);
    }

    port = atoi(argv[2]);

    printf("Puerto %d\n",port);
    printf("Type %d\n",type);
    printf("NumThreads %d\n",numThreads);

    RunServer(&server, port, type, numThreads);

    return (0);
}