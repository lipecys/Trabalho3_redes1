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
    sem_t full;
    sem_t empty;
    pthread_mutex_t mutex;
    lista *mensagens;
}produtor_consumidor;

typedef struct {
    char computer_number;
    const char *ip_address;
    const char *port;    
    Boolean bastao;
    produtor_consumidor threads;
}info_pkg;

info_pkg *inicializa_info(void);
void *insere_buffer(info_pkg *config_node);
void *retira_buffer(info_pkg *config_node);

#endif /* Fim de BIBLIOTECA_H */
