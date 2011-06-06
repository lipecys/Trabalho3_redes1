#include "client.h"

/* Função do Cliente - Utilizado para retirar mensagens da rede e inseri-las no buffer */
void * cliente (info_pkg *config_node) {
    client_server_info * client;
    char buf[4096];
    int numbytes;

    client = config_client(config_node->port, config_node->ip_address);

    while (TRUE) {
        // Trata mensagens aqui
        if ((numbytes = recv(client->sockfd, buf, MAX_BUFF_SIZE-1, 0)) == -1) {
            perror("recv");
            exit(1);
        }
        buf[numbytes] = '\0';
//        printf("client: received '%s'\n",buf);


        if (strcmp(buf+3,"MSG_DE_BASTAO" ))
        {
            config_node->bastao = TRUE;
        }
        else
        {
            // if destino == computer_number
            if(buf[0] == config_node->computer_number)
            {
                // setando aceitação para 1
                buf[2] == 1;
                printf("%s\n", buf+3);
                // se destino for diferente do computer_number insere na lista de repasse, senão não faz nada
                if(buf[1] != config_node->computer_number)
                {
                    // Início região crítica
                    sem_wait(&config_node->threads.empty_repassa);
                    pthread_mutex_lock(&config_node->threads.mutex_repassa);

                    insere_lista_fim((objeto)buf, config_node->threads.repassa);

                    pthread_mutex_unlock(&config_node->threads.mutex_repassa);
                    sem_post(&config_node->threads.full_repassa);
                    // Fim região crítica
                }
                
            }
            else
            {
                
                sleep(1);

                // Início região crítica
                sem_wait(&config_node->threads.empty_repassa);
                pthread_mutex_lock(&config_node->threads.mutex_repassa);

                insere_lista_fim((objeto)buf, config_node->threads.repassa);

                pthread_mutex_unlock(&config_node->threads.mutex_repassa);
                sem_post(&config_node->threads.full_repassa);
                // Fim região crítica
            }
        }
        buf[0] = '\0';
    }
    close(client->sockfd);
    pthread_exit((void*)1);
}
