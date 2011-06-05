#include "server.h"

/* Função do Servidor - Utilizado para inserir mensagens no buffer e reenvia-las */
void *servidor (info_pkg *config node) {
    client_server_info *server;
    int newconn;

    server = config_server(config_node->port);
    newconn = accept();

    while (TRUE) {
        if (config_node->bastao == TRUE) {
        }
    }
}
