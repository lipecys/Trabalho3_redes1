#include "fifo.h"

/* Função Retorna Primeiro nó da Lista */
no *primeiro_no(lista *l) { return l->primeiro;}

/* Função Retorna o Próximo nó à Partir do nó Corrente */
no *sucessor_no(no *p, lista *l) { return p->sucessor;}

/* Função Retorna Último nó da Lista */
no *ultimo_no(lista *l) { return l->ultimo;}

/* Função Retorna o Conteúdo do Objeto nó*/
objeto objeto_no(no *p) { return p->o;}

/* Função Retorna o Resultado da Comparação do Tamanho da Lista com Zero */
int vazia_lista(lista *l) { return tamanho_lista(l) == 0;}

/* Função Retorna o Tamanho da Lista */
unsigned int tamanho_lista(lista *l) { return l->tamanho;}

/* Função de Construção da Lista */
lista *constroi_lista(void) {

    lista *l = malloc(sizeof(lista));

    if ( ! l ) return NULL;

    l->primeiro = l->ultimo = NULL;  
    l->tamanho = 0;

    return l;
}

/* Função de Finalização da Lista */
void destroi_lista(lista *l) { 

    no *p;

    /* Último não presisa ser considerado, pois será apagado de qualquer forma */
    while ( (p = primeiro_no(l)) ) {

        l->primeiro = sucessor_no(p,l);
        free(p);
    }

    free(l);
}

/* Insere Objeto ao Final da Lista */
no *insere_lista_fim(objeto o, lista *l) {

    no *novo = malloc(sizeof(no));

    if ( ! novo ) return NULL;

    if ( vazia_lista(l) ) l->primeiro = novo;
    else l->ultimo->sucessor = novo;

    novo->o = o;
    novo->sucessor = NULL;
    ++l->tamanho;

    return l->ultimo = novo;
}

/* Função de Remoção de Objeto da Lista */
objeto remove_lista(lista *l) { 

    no *primeiro = primeiro_no(l);
    objeto o;

    if ( ! primeiro ) return NULL;

    o = objeto_no(primeiro);

    if ( l->primeiro == l->ultimo )
        l->ultimo = sucessor_no(primeiro,l);

    l->primeiro = sucessor_no(primeiro,l);
    --l->tamanho;
    free(primeiro);

    return o;
}

