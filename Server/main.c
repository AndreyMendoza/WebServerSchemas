#include "headers/server.h"
#include "headers/List.h"

int main() {

    Server *s = {NULL, NULL};
    RunServer(&s, 5050, 1, 1);
}