#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

/* Seção de Includes */
#include <pthread.h>
#include <semaphore.h>
#include <bits/local_lim.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "fifo.h"
#include "biblioteca.h"

#define CREATE_TOKEN 1

#define MAX_BUFF_SIZE 4096
#define CONTINUA 1
#define EOL '\n'

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

typedef struct {
    sem_t full;
    sem_t empty;
    pthread_mutex_t mutex;
    lista *mensagens;
}produtor_consumidor;

info_pkg *inicializa_info(void);

void *insere_buffer(produtor_consumidor *prod_cons);
void *retira_buffer(produtor_consumidor *prod_cons);
produtor_consumidor *cria_prod_cons(void);

#endif /* Fim de BIBLIOTECA_H */
