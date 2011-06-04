#include "socket.h"

// CRIA SOCKET
int inicializa_socket() {
    int sockfd = 0;
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == ERRO) {
        int errsv = errno;
        fprintf(stderr, "Falha %c ao iniciar conexao do Socket\n", errsv);
        return ERRO;       
    }
    
    return sockfd;
}
// OPÇÕES DE SOCKET

int fecha_socket(int sockfd) {
    if (shutdown(sockfd, SHUT_RDWR) == ERRO){
        int errsv = errno;
        fprintf(stderr, "Falha %c ao encerrar conexao do Socket\n", errsv);
        return ERRO;
    }

    return OK;
}