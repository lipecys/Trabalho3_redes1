#include "client.h"

/* Função do Cliente - Utilizado para retirar mensagens da rede e inseri-las no buffer */
void *cliente (info_pkg *config_node) {
    client_server_info *client;

    client = config_client(config_node->port, config_node->ip_address);

    while (TRUE) {
        // Trata mensagens aqui
        //if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        //    perror("recv");
        //    exit(1);
        //}
        //buf[numbytes] = '\0';
        //printf("client: received '%s'\n",buf);
    }
    close(client->sockfd);
}
