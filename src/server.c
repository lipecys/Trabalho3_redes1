#include "server.h"

/* Função do Servidor - Utilizado para inserir mensagens no buffer e reenvia-las */
void * servidor (info_pkg *config_node) {
    client_server_info *server;
    struct sockaddr_in cliaddr;
    socklen_t clilen;
    int newconn;

    server = config_server(config_node->port);
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
        }
        close(server->sockfd);
    }
}
