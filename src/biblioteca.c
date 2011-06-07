#include "biblioteca.h"

/* Inicializa_Info - inicializa estrutura de informações para quem pedir */
info_pkg *inicializa_info(void) {
    info_pkg *cria_info = (info_pkg *) malloc(sizeof(info_pkg));

    cria_info->threads.mensagens = constroi_lista();
    cria_info->threads.repassa = constroi_lista();

    cria_info->bastao = FALSE;



    cria_info->threads.confirmacao = 0;



    sem_init(&(cria_info->threads.full), 0, 0);
    sem_init(&(cria_info->threads.empty), 0, MAX_BUFF_SIZE);
    pthread_mutex_init(&(cria_info->threads.mutex), NULL);

    sem_init(&(cria_info->threads.full_repassa), 0, 0);
    sem_init(&(cria_info->threads.empty_repassa), 0, MAX_BUFF_SIZE);
    pthread_mutex_init(&(cria_info->threads.mutex_repassa), NULL);

    return cria_info;
}
