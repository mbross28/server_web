//
// Created by Mathis Brosseau on 16/09/2025.
//

#include "../include/client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8080
#define SERVER_IP "127.0.0.1"

int start_client() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Création de la socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);

    // Conversion de l'adresse IP
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        return -1;
    }

    // Connexion au serveur
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    // Envoi de la requête HTTP GET
    char *http_request =
            "GET / HTTP/1.1\r\n"
            "Host: localhost\r\n"
            "Connection: close\r\n"
            "\r\n";

    send(sock, http_request, strlen(http_request), 0);
    printf("Requête envoyée au serveur.\n");

    // Réception de la réponse
    int valread;
    printf("Réponse reçue :\n");
    while ((valread = read(sock, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[valread] = '\0';
        printf("%s", buffer);
    }
    close(sock);
    return 0;
}
