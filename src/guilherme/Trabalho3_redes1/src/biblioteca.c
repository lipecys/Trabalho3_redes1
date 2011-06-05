#include "biblioteca.h"

/* Inicializa_Info - inicializa estrutura de informações para quem pedir */
info_pkg *inicializa_info(void) {
    info_pkg *cria_info = (info_pkg *) malloc(sizeof(info_pkg));


    cria_info->bastao = FALSE;

    sem_init(&(cria_info->threads.full), 0, 0);
    sem_init(&(cria_info->threads.empty), 0, MAX_BUFF_SIZE);

    pthread_mutex_init(&(cria_info->threads.mutex), NULL);


    return cria_info;
}


/* Produtor insere no buffer */
void *insere_buffer(info_pkg *config_node) {
    do {
        int tam_buffer = 256;
        char *buffer = (char *) malloc(tam_buffer * sizeof(char));
        int cont_caracteres = 0;
        char *string_final;

        buffer[cont_caracteres] = getchar();
        while (buffer[cont_caracteres] != EOL)
        {
            cont_caracteres++;
            if ( cont_caracteres == tam_buffer )
           {
                tam_buffer *= 2;
                buffer = (char *) realloc(buffer, tam_buffer * sizeof(char));
            }
            buffer[cont_caracteres] = getchar();
        }

        // criando uma string do tamanho da entrada lida
        string_final = (char *) malloc( cont_caracteres * sizeof(char));
        memcpy(string_final, buffer, cont_caracteres);


        // Início região crítica
        sem_wait(&config_node->threads.empty);
        pthread_mutex_lock(&config_node->threads.mutex);


        // inserir novo item na fila
        insere_lista_fim((objeto)string_final, config_node->threads.mensagens);


        pthread_mutex_unlock(&config_node->threads.mutex);
        sem_post(&config_node->threads.full);
        // Fim região crítica

        free(buffer);
    } while(CONTINUA);

    pthread_exit((void*)0);
}

/* Consumidor retira do buffer */
void *retira_buffer(info_pkg *config_node) {
    do {
        // Início região crítica
        sem_wait(&config_node->threads.full);
        pthread_mutex_lock(&config_node->threads.mutex);


        // consome item da fila
        if (config_node->threads.mensagens->tamanho == 5)
        {
            while(!vazia_lista(config_node->threads.mensagens))
            {
                /* <<FELIPE>> envia mensagem*/
                printf("%s\n", (char *)remove_lista(config_node->threads.mensagens));
            }
        }


        pthread_mutex_unlock(&config_node->threads.mutex);
        sem_post(&config_node->threads.empty);
        // Fim região crítica
    } while(CONTINUA);


    pthread_exit((void*)1);
}
