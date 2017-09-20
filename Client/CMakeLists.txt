cmake_minimum_required(VERSION 3.8)
project(Client)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c headers/client.h source/client.c headers/List.h source/List.c)
find_package( Threads REQUIRED )
add_executable(Client ${SOURCE_FILES})
target_link_libraries( Client Threads::Threads )