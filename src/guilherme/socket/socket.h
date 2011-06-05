#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>

#define ERRO -1
#define OK    0

typedef struct {
    int sockfd;
    struct addrinfo hints;
}client_server_info;

int inicializa_socket(client_server_info *info_sock);
int fecha_socket(int sockfd);
client_server_info *config_client(const char *port, const char *prox_maq);
client_server_info *config_server(const char *port);
#endif /* Fim de SOCKET_H */
