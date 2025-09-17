//
// Created by Mathis Brosseau on 16/09/2025.
//

#include "../include/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int start_server() {
    struct sockaddr_in server_addr;
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1) {
        perror("socket failed");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_fd);
        return -1;
    }

    if (listen(server_fd, BACKLOG) < 0) {
        perror("listen failed");
        close(server_fd);
        return -1;
    }

    printf("Serveur en écoute sur le port %d...\n", PORT);

    while (1) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) {
            perror("accept failed");
            continue;
        }

        handle_client(client_fd);
        close(client_fd);
    }
    close(server_fd);
    return 0;
}

int handle_client(int client_fd) {
    char buffer[1024] = {0};
    read(client_fd, buffer, sizeof(buffer) - 1);
    printf("Requête reçue :\n%s\n", buffer);

    char response[] =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "\r\n"
            "<html><body>"
            "<h1>Hello tout le monde!</h1>"
            "<div><textarea id=\"story\" name=\"story\" rows=\"5\" cols=\"33\"></textarea><button>Interpreter</button></div>"
            "<div></div>"
            "</body></html>";

    write(client_fd, response, strlen(response));

    return 0;
}

//system(python monsctipt)