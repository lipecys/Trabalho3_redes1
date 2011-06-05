#include "biblioteca.h"

/* Função principal - Responsavel por repassar parâmetros e inicializar
 * as threads de leitura e escrita */
int main(const int argc, const char *argv[]) {
    info_pkg *config_node = inicializa_info();
    produtor_consumidor *prod_cons = cria_prod_cons();
    pthread_t prod, cons;

    prod_cons->mensagens = constroi_lista();

    if(argc != 4) {
        fprintf(stderr, "Numero invalido de parametros\n");
        exit(EXIT_FAILURE);
    }

    config_node->ip_address = argv[1];
    config_node->port = atoi(argv[2]);
    config_node->computer_number = atoi(argv[3]);
    if (config_node->computer_number == CREATE_TOKEN) {
        config_node->bastao = TRUE;
    }
    
    printf("IPADDRESS: %s PORT: %d NUMBER: %d BASTAO: %d\n", config_node->ip_address, config_node->port, config_node->computer_number, config_node->bastao);

    pthread_create(&prod, NULL, (void *)&insere_buffer, (void*)prod_cons);
    pthread_create(&cons, NULL, (void*)&retira_buffer, (void*)prod_cons);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    //fecha_socket(config_node->sockfd);
    exit(EXIT_SUCCESS);
}
