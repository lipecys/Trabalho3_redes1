#ifndef FIFO_H
#define FIFO_H

/* Includes necessários para a pilha funcionar */
#include <stdio.h>
#include <malloc.h>
#include <string.h>

/* Definição da Estrutura utilizada na fila de envio */
typedef void *objeto;

typedef struct no {
  objeto o;
  struct no *sucessor;
} no;

typedef struct {
  no *primeiro;
  no *ultimo;
  unsigned int tamanho;
} lista;

/* Funções utilizadas para obter informações básicas da lista */
no *primeiro_no(lista *l);
no *sucessor_no(no *p, lista *l);
no *ultimo_no(lista *l);
objeto objeto_no(no *p);
int vazia_lista(lista *l);
unsigned int tamanho_lista(lista *l);

/* Funções de alto nível utilizadas na manipulação da lista */
lista *constroi_lista(void);
void destroi_lista(lista *l);
no *insere_lista_fim(objeto o, lista *l);
objeto remove_lista(lista *l);

#endif
