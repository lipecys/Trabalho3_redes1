#include "client.h"

/* Função do Cliente - Utilizado para retirar mensagens da rede e inseri-las no buffer */
void * cliente (info_pkg *config_node) {
    client_server_info * client;
    char buf[MAX_BUFF_SIZE];
//    char *buf;
    int numbytes;

//    puts("C1");

    client = config_client(config_node->port, config_node->ip_address);

//    puts("C2");

    while (TRUE) {
//        puts("C3");
//        buf = (char *) malloc(MAX_BUFF_SIZE * sizeof(char));
        // Trata mensagens aqui
        if ((numbytes = recv(client->sockfd, buf, MAX_BUFF_SIZE-1, 0)) == -1) {
            perror("recv");
            exit(1);
        }
        buf[numbytes] = '\0';

//printf("DESTINO: %c\n", buf[0]);
//printf("ORIGEM: %c\n", buf[1]);
//        if (strcmp(buf+3,"MSG_DE_BASTAO" ))
        if (strcmp(buf,"MSG_DE_BASTAO"))
        {
            config_node->bastao = TRUE;
        }
        else
        {
            // if destino é igual a computer_number
            if(atoi(&buf[0]) == atoi(&config_node->computer_number))
            {
                // setando aceitação para 1
                buf[2] = '1';
                printf("%s\n", buf+3);
                // se origem for diferente do computer_number insere na lista de repasse, senão não faz nada
                if(atoi(&buf[1]) != atoi(&config_node->computer_number))
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


//Adicionei esse if para liberar o envio da próxima msg no server
            if(atoi(&buf[1]) == atoi(&config_node->computer_number) && atoi(&buf[2]))
            {
                config_node->threads.confirmacao = 1;
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
//        puts("C4");
        buf[0] = '\0';
    }
    close(client->sockfd);
    pthread_exit((void*)1);
}
