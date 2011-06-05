#include "socket.h"

/* Função Inicializa um Socket */
int inicializa_socket(client_server_info *info_sock) {
    
    if ((info_sock->sockfd = socket(info_sock->hints.ai_family, info_sock->hints.ai_socktype, info_sock->hints.ai_protocol)) == ERRO) {
        int errsv = errno;
        fprintf(stderr, "Falha %c ao criar o Socket\n", errsv);
        return ERRO;       
    }

    return OK;
}

/* Função para setar as configurações do socket do cliente */
client_server_info *config_client(unsigned short int port, const char *prox_maq) {
    client_server_info *client = (client_server_info *) calloc(sizeof(client_server_info));
    struct addrinfo *servinfo;
    int rv;

    client->sokfd = inicializa_socket();

    client->hints.ai_family = AF_INET;
    client->hints.ai_socktype = SOCK_STREAM;
    client->hints.ai_flags = AI_PASSIVE;
    client->hints.ai_protocol = 0;
    client->hints.ai_canonname = NULL

    if ((rv = getaddrinfo(argv[1], port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    client->sock_addr.sin_port = htons(port);

    return client;
}

/* Função para setar as configurações do socket do servidor */
client_server_info *config_server(unsigned short int port) {
    client_server_info *server = (client_server_info *) calloc(sizeof(client_server_info));
    struct addrinfo *result, *r;
    int rv;

    server->sokfd = inicializa_socket();

    server->hints.ai_family = AF_INET;
    server->hints.ai_socktype = SOCK_STREAM;
    server->hints.ai_flags = AI_PASSIVE;
    server->hints.ai_protocol = 0;
    server->hints.ai_canonname = NULL;
    server->hints.ai_addr = NULL;
    server->hints.ai_next = NULL;

    if ((rv = getaddrinfo(argv[1], port, server->hints, &result)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(EXIT_FAILURE);
    }

    for (r = result; r != NULL; r = r->ai.next) {
        if ((server->sockfd = socket(r->ai_family, r->ai_socktype, r->ai_protocol)) == ERRO)
            continue;

        if (bind(server->sockfd, r->ai_addr, r->ai_addr) == OK)
            break;

        close(server->sockfd);
    }

    if (r == NULL) {
        fprintf (stderr, "Falha ao realizar o bind da conexao.\n");
        exit(EXIT_FAILURE);
    }

    if (listen(server->sockfd, BACKLOG) == ERRO) {
        int errsv = errno;
        fprintf (stderr, "Falha %d ao realizar o listen.\n", errsv);
        exit(EXIT_FAILURE);
    }

    return server;
}

/* Função Finaliza Conexões em um Socket */
int fecha_socket(client_server_info *info_sock) {
    if (close(info_sock->sockfd) == ERRO){
        int errsv = errno;
        fprintf(stderr, "Falha %c ao finalizar o Socket\n", errsv);
        return ERRO;
    }

    return OK;
}

/*
client_socket_t *init_client(unsigned int port, const char *next_maq) {
    struct hostent *hp;

    client_socket_t *client = (client_socket_t *)malloc(sizeof(client_socket_t));
    client->descriptor = socket(AF_INET, SOCK_DGRAM, 0);

    if(client->descriptor < 0) error("socket");

    client->sock_addr.sin_family = AF_INET;
    hp = gethostbyname(next_maq);

    if (hp==0) error("Unknown host");

    bcopy((char *)hp->h_addr, (char *)&client->sock_addr.sin_addr, hp->h_length);

    client->sock_addr.sin_port = htons(port);

    return client;
}

server_socket_t *init_server(unsigned int port) {
    unsigned int length;

    server_socket_t *sock_server = (server_socket_t *)malloc(sizeof(server_socket_t));

    struct sockaddr_in server;

    sock_server->descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_server->descriptor < 0) error("Opening socket");

    length = sizeof(server);
    bzero(&server, length);

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(port);

    if (bind(sock_server->descriptor,(struct sockaddr *)&server,length) < 0)
        error("binding");

    return sock_server;
}*/