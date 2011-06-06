#include "client.h"

/* Função do Cliente - Utilizado para retirar mensagens da rede e inseri-las no buffer */
void * cliente (info_pkg *config_node) {
/*    client_server_info * client;

    client = config_client(config_node->port, config_node->ip_address);

    while (TRUE) {
        // Trata mensagens aqui
        //if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        //    perror("recv");
        //    exit(1);
        //}
        //buf[numbytes] = '\0';
        //printf("client: received '%s'\n",buf);
*/


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


/*    }
    close(client->sockfd);
*/
}
