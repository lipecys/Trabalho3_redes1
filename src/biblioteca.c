#include "biblioteca.h"

/* Inicializa_Info - inicializa estrutura de informações para quem pedir */
info_pkg *inicializa_info(void) {
    info_pkg *cria_info = (info_pkg *) malloc(sizeof(info_pkg));

    cria_info->threads.mensagens = constroi_lista();
    cria_info->threads.reenvio = constroi_lista();

    cria_info->bastao = FALSE;

    sem_init(&(cria_info->threads.full), 0, 0);
    sem_init(&(cria_info->threads.empty), 0, MAX_BUFF_SIZE);
    pthread_mutex_init(&(cria_info->threads.mutex), NULL);

    sem_init(&(cria_info->threads.full_reenvio), 0, 0);
    sem_init(&(cria_info->threads.empty_reenvio), 0, MAX_BUFF_SIZE);
    pthread_mutex_init(&(cria_info->threads.mutex_reenvio), NULL);

    return cria_info;
}
