#include "server.h"

/* Função do Servidor - Utilizado para inserir mensagens no buffer e reenvia-las */
void * servidor (info_pkg *config_node) {
    client_server_info * server;
    struct sockaddr_in cliaddr;
    socklen_t clilen;
    int newconn;
    
/*    server = config_server(config_node->port);
    clilen = sizeof(cliaddr);
    newconn = accept(server->sockfd, (struct sockaddr *)&cliaddr, &clilen);
    
    if (!fork()) {
        close(server->sockfd);
        while (TRUE) {
            //if (send(new_fd, "Hello, world!", 13, 0) == -1) {
            //    sleep(1);
            //}
        }
        close(newconn);
    }
    else {
        close(newconn);
        while(TRUE) {
            //puts("Entre com a string");
            //gets(str);
            //puts(str);
*/


            do {
                int tam_buffer = 256;
                char *buffer = (char *) malloc(tam_buffer * sizeof(char));
                int cont_caracteres = 0;
                char *string_final;
                char destino;

                printf("Especifique o destino (1 a 4):\n");
                destino = getchar();

                getchar();

                printf("Digite a mensagem:\n");


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

                /*
                * criando uma string do tamanho da entrada lida
                * O + 4 é porque precisamos dos seguintes bits de controle:
                * - destino
                * - origem
                * - aceitação 
                * - '\0' da string
                */
                string_final = (char *) malloc( (cont_caracteres + 4)* sizeof(char));
                memcpy(string_final+3, buffer, cont_caracteres);
                string_final[0] = destino;
                string_final[1] = config_node->computer_number;
                string_final[2] = '0';
                string_final[cont_caracteres+3] = '\0';

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


/*        }
        close(server->sockfd);
    }
*/
}
