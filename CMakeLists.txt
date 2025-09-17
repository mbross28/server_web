cmake_minimum_required(VERSION 4.0)
project(Serveur_web C)

set(CMAKE_C_STANDARD 17)

add_executable(Serveur_web main.c include/server.h src/server.c include/client.h src/client.c)