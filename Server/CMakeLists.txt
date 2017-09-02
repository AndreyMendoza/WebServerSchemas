cmake_minimum_required(VERSION 3.8)
project(Server)

set(CMAKE_C_STANDARD 11)



set(SOURCE_FILES main.c headers/server.h source/server.c)
find_package( Threads REQUIRED )
add_executable(Server ${SOURCE_FILES})
target_link_libraries( Server Threads::Threads )