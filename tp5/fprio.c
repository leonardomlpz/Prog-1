// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Implementação com lista encadeada simples

#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

// A COMPLETAR

struct fprio_t *fprio_cria (){
    struct fprio_t *primeiro;
    if (! (primeiro = malloc(sizeof(struct fprio_t))) );
        return NULL;

    primeiro->prim = NULL;
    primeiro->num = 0;

    return primeiro;
}

int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio){
    if (f == NULL || item == NULL)
        return -1;
    struct fpnodo_t *novo;
    if (! (novo = mallco(sizeof(struct fpnodo_t))) );
        return -1;

    novo->item = item;
    novo->prio = prio;
    novo->prox = NULL;
    novo->tipo = tipo;
    //fila vazia
    if (f->num == 0)
    {
        f->prim = novo;
        f->num++;

        return f->num;
    }
    
    struct fpnodo_t *aux;
    aux = f->prim;
    while (prio > aux->prio || aux->prox != NULL)
        aux = aux->prox;
}