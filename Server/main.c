#include "headers/server.h"
#include "headers/List.h"

int main() {

//    RunServers();
    Server *s = {NULL, NULL};
    RunServer(&s, 5050);
}