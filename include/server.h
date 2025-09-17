//
// Created by Mathis Brosseau on 16/09/2025.
//
#ifndef SERVER_H
#define SERVER_H

#define PORT 8080
#define BACKLOG 5

int start_server();
int handle_client(int client_fd);

#endif
