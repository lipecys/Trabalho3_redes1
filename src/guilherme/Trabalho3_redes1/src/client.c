#include "client.h"

/* Função do Cliente - Utilizado para retirar mensagens da rede e inseri-las no buffer */
void *cliente (info_pkg *config node) {
    client_server_info *client;

    client = config_client(config_node->port, config_node->ip_address);

    while (TRUE) {
        if (config_node->bastao == TRUE) {
        }
    }


}
