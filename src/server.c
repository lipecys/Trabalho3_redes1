#include "server.h"

/* Função do Servidor - Utilizado para inserir mensagens no buffer e reenvia-las */
void * servidor (info_pkg *config_node) {
    client_server_info *server;
    struct sockaddr_in cliaddr;
    socklen_t clilen;
    int newconn;
    time_t seconds;
//    char *passa_bastao;

//    puts("S1");

    server = config_server(config_node->port);
    clilen = sizeof(cliaddr);
    newconn = accept(server->sockfd, (struct sockaddr *)&cliaddr, &clilen);

//    puts("S2");
    // IF -> quem vai enviar
    // ELSE -> quem vai inserir na lista para envio
    close(server->sockfd); // child doesn't need the listener
    while(TRUE) {
//	puts("S3");
	if (config_node->bastao == TRUE) {
//        puts("Estou com o bastao");
	    seconds = time(NULL);
	    while (!vazia_lista(config_node->threads.mensagens) && (time(NULL)-seconds <= 5 )) {
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

/*
        passa_bastao = (char *) malloc( 3*sizeof(char) + strlen("MSG_DE_BASTAO")*sizeof(char) + 1);
        passa_bastao[0] = config_node->computer_number+1;
        passa_bastao[1] = config_node->computer_number;
        passa_bastao[2] = '0';
        memcpy(passa_bastao+3, "MSG_DE_BASTAO", strlen("MSG_DE_BASTAO"));
        passa_bastao[3 + strlen("MSG_DE_BASTAO")] = '\0';

        printf("%s\n",passa_bastao);

	    if (send(newconn, passa_bastao, strlen(passa_bastao), 0) == -1)
*/

	    if (send(newconn, "MSG_DE_BASTAO", strlen("MSG_DE_BASTAO"), 0) == -1)
		    perror("send");
	}
	else {
//        puts("Não estou com o bastão");
	    if (!vazia_lista(config_node->threads.repassa)) {
		    char *buffer;

		    sem_wait(&config_node->threads.full_repassa);
		    pthread_mutex_lock(&config_node->threads.mutex_repassa);
		    // Início região crítica
		
		    buffer = (char *)remove_lista(config_node->threads.repassa);

		    // Fim região crítica
		    pthread_mutex_unlock(&config_node->threads.mutex_repassa);
		    sem_post(&config_node->threads.empty_repassa);

		if (send(newconn, buffer, strlen(buffer), 0) == -1)
		    perror("send");
		free(buffer);
	    }
	}
//	puts("S4");
    }
    pthread_exit((void*)0);
}
