#include "server.h"

/* Função do Servidor - Utilizado para inserir mensagens no buffer e reenvia-las */
void * servidor (info_pkg *config_node) {
    client_server_info *server;
    struct sockaddr_in cliaddr;
    socklen_t clilen;
    int newconn;
    time_t seconds;

    server = config_server(config_node->port);
    clilen = sizeof(cliaddr);
    newconn = accept(server->sockfd, (struct sockaddr *)&cliaddr, &clilen);

    // IF -> quem vai enviar
    // ELSE -> quem vai inserir na lista para envio
	if (!fork()) { // this is the child process
		close(server->sockfd); // child doesn't need the listener
        while(TRUE)
        {
            if (config_node->bastao == TRUE)
            {
                seconds = time(NULL);
                while (!vazia_lista(config_node->threads.mensagens) && (time(NULL)-seconds <= 5 ))
                {
                    char *buffer;
                    // Início região crítica
                    sem_wait(&config_node->threads.full);
                    pthread_mutex_lock(&config_node->threads.mutex);

                    // consome item da fila
                    // <<FELIPE>> envia mensagem
                    buffer = (char *)remove_lista(config_node->threads.mensagens);

                    pthread_mutex_unlock(&config_node->threads.mutex);
                    sem_post(&config_node->threads.empty);
                    // Fim região crítica

                    if (send(newconn, buffer, strlen(buffer), 0) == -1)
                       perror("send");
                    // espera a mensagem dar uma volta no anel para ver se foi recebida corretamente
                    // e então passa para a próxima mensagem, ou envia a mesma novamente
//                    sleep(4);
                    while (config_node->threads.confirmacao);
                    config_node->threads.confirmacao = 0;
                }
                // Enviar TOKEN

                config_node->bastao = FALSE;
                
                if (send(newconn, "MSG_DE_BASTAO", strlen("MSG_DE_BASTAO"), 0) == -1)
                       perror("send");
            }
            else
            {
                if (!vazia_lista(config_node->threads.repassa))
                {
                    char *buffer;
                    // Início região crítica
                    sem_wait(&config_node->threads.full_repassa);
                    pthread_mutex_lock(&config_node->threads.mutex_repassa);

                    buffer = (char *)remove_lista(config_node->threads.repassa);

                    pthread_mutex_unlock(&config_node->threads.mutex_repassa);
                    sem_post(&config_node->threads.empty_repassa);
                    // Fim região crítica

                    if (send(newconn, buffer, strlen(buffer), 0) == -1)
                       perror("send");
                    free(buffer);
                }
            }
        }
	}
	else {
        close(newconn);
        while(TRUE) {
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

            
//                * criando uma string do tamanho da entrada lida
//                * O + 4 é porque precisamos dos seguintes bits de controle:
//                * - destino
//                * - origem
//                * - aceitação 
//                * - '\0' da string
            
            string_final = (char *) malloc( (cont_caracteres + 4)* sizeof(char));
            memcpy(string_final+3, buffer, cont_caracteres);
            string_final[0] = destino;
            string_final[1] = config_node->computer_number;
            string_final[2] = '0';
//            string_final[cont_caracteres+3] = '\0';
//            snprintf(string_final, 3 * sizeof(char) + strlen(buffer)*sizeof(char) + 1, "%c%c0%s\0", destino, config_node->computer_number, buffer);

            // Início região crítica
            sem_wait(&config_node->threads.empty);
            pthread_mutex_lock(&config_node->threads.mutex);


            // inserir novo item na fila
            insere_lista_fim((objeto)string_final, config_node->threads.mensagens);


            pthread_mutex_unlock(&config_node->threads.mutex);
            sem_post(&config_node->threads.full);
            // Fim região crítica


            //free(buffer);
        }
    }
    close(server->sockfd);
    pthread_exit((void*)0);
}
