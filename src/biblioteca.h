#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

/* Seção de Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "socket.h"

#define CREATE_TOKEN 1

typedef enum {
    FALSE,
    TRUE
} Boolean;

/* Seção de Definições de Estruturas */
typedef struct {
    int sockfd;
    const char *ip_address;
    unsigned short int port;
    unsigned char computer_number;
    Boolean bastao;
}info_pkg;

info_pkg *inicializa_info(void);
#endif /* Fim de BIBLIOTECA_H */
