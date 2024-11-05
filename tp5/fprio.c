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
    //primeiro item da fila tem menos prioridade
    if (aux->prio > prio)
    {
        novo->prox = aux;
        f->prim = novo;
        f->num++;

        return f->num;
    }
    //caminha se a prioridade for menor
    //para se chegar no ultimo item
    while (prio > aux->prox->prio || aux->prox != NULL)
        aux = aux->prox;
    //insere o item
    novo->prox = aux->prox;
    aux->prox = novo;
    f->num++;

    return f->num;
}

struct fprio_t *fprio_destroi (struct fprio_t *f){
    struct fpnodo_t *aux;

    if (f == NULL || f->num < 0)
        return NULL;
    
    while (aux != NULL)
    {
        struct fpnodo_t *temp = aux;
        //move para o proximo
        aux = aux->prox;
        //libera o atual
        free (temp->item);
        free (temp);
        temp = NULL;
    }

    free (f);
    f = NULL;

    return NULL;
}

void *fprio_retira (struct fprio_t *f, int *tipo, int *prio){
    if (f == NULL || tipo == NULL || prio == NULL)
        return NULL;

    if (f->num == 0)
        return NULL;

    struct fpnodo_t *aux;
    aux = f->prim;
    if (f->num == 1)
    {
        *tipo = aux->tipo;
        *prio = aux->prio;
        free (aux->item);
        free (aux);
        aux = NULL;
        f->num--;

        return;
    }
    f->prim = aux->prox;
}