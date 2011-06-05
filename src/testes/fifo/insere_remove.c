#include <pthread.h>
#include <semaphore.h>
#include <bits/local_lim.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fifo.h"
#include "biblioteca.h"


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

int main() {
    produtor_consumidor *prod_cons = cria_prod_cons();

    prod_cons->mensagens = constroi_lista();

    pthread_t prod, cons;

    pthread_create(&prod, NULL, (void *)&insere_buffer, (void*)prod_cons);
    pthread_create(&cons, NULL, (void*)&retira_buffer, (void*)prod_cons);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
