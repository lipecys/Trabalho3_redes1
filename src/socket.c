#include "socket.h"

/* Função Inicializa um Socket */
int inicializa_socket(client_server_info *info_sock) {
    int sockfd;

    if ((sockfd = socket(info_sock->hints.ai_family, info_sock->hints.ai_socktype, info_sock->hints.ai_protocol)) == ERRO) {
        int errsv = errno;
        fprintf(stderr, "Falha %c ao criar o Socket\n", errsv);
        return ERRO;       
    }

    return sockfd;
}

/* Função Finaliza Conexões em um Socket */
int fecha_socket(int sockfd) {
    if (close(sockfd) == ERRO){
        int errsv = errno;
        fprintf(stderr, "Falha %c ao finalizar o Socket\n", errsv);
        return ERRO;
    }

    return OK;
}

/* Função para setar as configurações do socket do cliente */
client_server_info *config_client(const char *port, const char *prox_maq) {
    client_server_info *client = (client_server_info *) calloc( 1, sizeof(client_server_info));
    struct addrinfo *result, *r;
    int rv;

    client->hints.ai_family = AF_INET;
    client->hints.ai_socktype = SOCK_STREAM;
    client->hints.ai_flags = 0;
    client->hints.ai_protocol = 0;

    if ((rv = getaddrinfo(NULL, port, &(client->hints), &result)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(EXIT_FAILURE);
    }

    for (r = result; r != NULL; r = r->ai_next) {
        if ((client->sockfd = inicializa_socket(client)) == ERRO)
            continue;
        
        if (connect(client->sockfd, r->ai_addr, r->ai_addrlen) != ERRO)
            break;

        fecha_socket(client->sockfd);
    }

    if (r == NULL) {
        fprintf(stderr, "Cliente não consegui se conectar.\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);

    return client;
}

/* Função para setar as configurações do socket do servidor */
client_server_info *config_server(const char *port) {
    client_server_info *server = (client_server_info *) calloc( 1, sizeof(client_server_info));
    struct addrinfo *result, *r;
    int rv;

    server->hints.ai_family = AF_INET;
    server->hints.ai_socktype = SOCK_STREAM;
    server->hints.ai_flags = AI_PASSIVE;
    server->hints.ai_protocol = 0;
    server->hints.ai_canonname = NULL;
    server->hints.ai_addr = NULL;
    server->hints.ai_next = NULL;

    if ((rv = getaddrinfo(NULL, port, &(server->hints), &result)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(EXIT_FAILURE);
    }

    for (r = result; r != NULL; r = r->ai_next) {
        if ((server->sockfd = inicializa_socket(server)) == ERRO)
            continue;

        if (bind(server->sockfd, r->ai_addr, r->ai_addrlen) == OK)
            break;

        fecha_socket(server->sockfd);
    }

    if (r == NULL) {
        fprintf (stderr, "Falha ao realizar o bind da conexao.\n");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(result);

    if (listen(server->sockfd, 1) == ERRO) {
        int errsv = errno;
        fprintf (stderr, "Falha %d ao realizar o listen.\n", errsv);
        exit(EXIT_FAILURE);
    }

    return server;
}
