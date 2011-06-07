#include "commandLineInterface.h"

void * commandline(info_pkg * config_node) {
    int cont_caracteres, tam_buffer;
    char *buffer, *string_final;
    char destino;
    
    while(TRUE) {
        buffer = (char *) malloc(tam_buffer * sizeof(char));
        tam_buffer = TAM_INI_BUFFER;
        cont_caracteres = 0;
        
        printf("Especifique o destino (1 a 4):\n");
        destino = getchar();
        getchar();
        
        printf("Digite a mensagem:\n");
        buffer[cont_caracteres] = getchar();
        while (buffer[cont_caracteres] != EOL) {
            cont_caracteres++;
            if ( cont_caracteres == tam_buffer ) {
                tam_buffer *= 2;
                buffer = (char *) realloc(buffer, tam_buffer * sizeof(char));
            }
            buffer[cont_caracteres] = getchar();
        }
        
        //                * criando uma string do tamanho da entrada lida
        //                * O + 4 é porque precisamos dos seguintes bits de controle:
        //                * - destino
        //                * - origem
        //                * - aceitação 
        //                * - '\0' da string
        
        string_final = (char *) malloc( (cont_caracteres + 4)* sizeof(char));
        memcpy(string_final+3, buffer, cont_caracteres);
        string_final[0] = destino;
        string_final[1] = config_node->computer_number;
        string_final[2] = '0';
        //            snprintf(string_final, 3 * sizeof(char) + strlen(buffer)*sizeof(char) + 1, "%c%c0%s\0", destino, config_node->computer_number, buffer);
        
        
        sem_wait(&config_node->threads.empty);
        pthread_mutex_lock(&config_node->threads.mutex);
        // Início região crítica
        
        // inserir novo item na fila
        insere_lista_fim((objeto)string_final, config_node->threads.mensagens);
        
        // Fim região crítica        
        pthread_mutex_unlock(&config_node->threads.mutex);
        sem_post(&config_node->threads.full);
    }
    pthread_exit((void*)0);
}
