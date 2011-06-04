#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>

#define ERRO -1
#define OK    0

int inicializa_socket();
int fecha_socket(int sockfd);
#endif /* Fim de SOCKET_H */
