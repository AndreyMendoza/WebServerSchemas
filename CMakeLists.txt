cmake_minimum_required(VERSION 3.8)
project(WebServerSchemas)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Client/headers/client.h
        Client/headers/List.h
        Client/source/client.c
        Client/source/List.c
        Client/main.c
        Server/headers/List.h
        Server/headers/server.h
        Server/source/List.c
        Server/source/server.c
        Server/main.c
        README.md)

add_executable(WebServerSchemas ${SOURCE_FILES})