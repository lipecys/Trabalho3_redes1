#include "biblioteca.h"

/* Função principal - Responsavel por repassar parâmetros e inicializar
 * as threads de cliente e servidor */
int main(const int argc, const char *argv[]) {
    info_pkg *config_node = inicializa_info();
    pthread_t prod, cons;
    int servidor;

    config_node->threads.mensagens = constroi_lista();

    if(argc != 2) {
        fprintf(stderr, "Número invalido de parametros\n");
        exit(EXIT_FAILURE);
    }

    servidor = atoi(argv[1]);

    switch (servidor)
    {
        case 1:
            printf("1\n");
            // aponta para a 2, mumm
            config_node->ip_address = "10.17.110.11";
            config_node->computer_number = 1;
            config_node->bastao = TRUE;
            break;
        case 2:
            printf("2\n");
            // aponta para a 3, priorat
            config_node->ip_address = "10.17.110.49";
            config_node->computer_number = 2;
            break;
        case 3:
            printf("3\n");
            // aponta para a 4, bowmore
            config_node->ip_address = "10.17.110.53";
            config_node->computer_number = 3;
            break;
        case 4:
            printf("4\n");
            // aponta para a 1, macalan
            config_node->ip_address = "10.17.110.6";
            config_node->computer_number = 4;
            break;
        default:
            printf("número de servidor inválido\n");
    }

    config_node->port = 10579;

    printf("IPADDRESS: %s PORT: %d NUMBER: %d BASTAO: %d\n", config_node->ip_address, config_node->port, config_node->computer_number, config_node->bastao);

    pthread_create(&prod, NULL, (void *)&cliente, (void*)config_node);
    pthread_create(&cons, NULL, (void*)&servidor, (void*)config_node);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    //fecha_socket(config_node->sockfd);
    exit(EXIT_SUCCESS);
}
