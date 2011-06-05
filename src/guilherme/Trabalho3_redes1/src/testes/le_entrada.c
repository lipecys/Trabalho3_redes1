#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONTINUA 1
#define EOL '\n'

int main ( int argc, char **argv)
{
    int tam_buffer = 256;
    char *buffer = (char *) malloc(tam_buffer * sizeof(char));
    int cont_caracteres = 0;
    char *string_final;

    buffer[cont_caracteres] = getchar();
    while (buffer[cont_caracteres] != EOL)
    {
        cont_caracteres++;
        if ( cont_caracteres == tam_buffer )
       {
            tam_buffer *= 2;
            buffer = (char *) realloc(buffer, tam_buffer * sizeof(char));
        }
        buffer[cont_caracteres] = getchar();
    }

    // criando uma string do tamanho da entrada lida
    string_final = (char *) malloc( cont_caracteres * sizeof(char));
    memcpy(string_final, buffer, cont_caracteres);

    printf("%s\n", string_final);

    free(string_final);
    free(buffer);
    return 0;
}
