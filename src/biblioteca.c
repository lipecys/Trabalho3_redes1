#include "biblioteca.h"

/* Inicializa_Info - inicializa estrutura de informações para quem pedir */
info_pkg *inicializa_info(void) {
    info_pkg *cria_info = (info_pkg *) malloc(sizeof(info_pkg));


    cria_info->bastao = FALSE;

    return cria_info;
}


/* Produtor insere no buffer */
void *insere_buffer(produtor_consumidor *prod_cons) {
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
        sem_wait(&prod_cons->empty);
        pthread_mutex_lock(&prod_cons->mutex);


        // inserir novo item na fila
        insere_lista_fim((objeto)string_final, prod_cons->mensagens);


        pthread_mutex_unlock(&prod_cons->mutex);
        sem_post(&prod_cons->full);
        // Fim região crítica

        free(buffer);
    } while(CONTINUA);

    pthread_exit((void*)0);
}

/* Consumidor retira do buffer */
void *retira_buffer(produtor_consumidor *prod_cons) {
    do {
        // Início região crítica
        sem_wait(&prod_cons->full);
        pthread_mutex_lock(&prod_cons->mutex);


        // consome item da fila
        if (prod_cons->mensagens->tamanho == 5)
        {
            while(!vazia_lista(prod_cons->mensagens))
            {
                /* <<FELIPE>> envia mensagem*/
                printf("%s\n", (char *)remove_lista(prod_cons->mensagens));
            }
        }


        pthread_mutex_unlock(&prod_cons->mutex);
        sem_post(&prod_cons->empty);
        // Fim região crítica
    } while(CONTINUA);


    pthread_exit((void*)1);
}


produtor_consumidor *cria_prod_cons(void) {
    produtor_consumidor *prod_cons = (produtor_consumidor *) malloc(sizeof(produtor_consumidor));

    sem_init(&(prod_cons->full), 0, 0);
    sem_init(&(prod_cons->empty), 0, MAX_BUFF_SIZE);

    pthread_mutex_init(&(prod_cons->mutex), NULL);

    return prod_cons;
}
