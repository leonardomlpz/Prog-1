// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Implementação do TAD - a completar
//
// Implementação com lista encadeada dupla não-circular

#include <stdio.h>
#include "lista.h"

struct lista_t *lista_cria (){
    struct lista_t *L;
    if (! (L = malloc(sizeof(struct lista_t))) )
        return NULL;
    
    L->prim = NULL;
    L->ult = NULL;
    L->tamanho = 0;

    return L;
}

int lista_insere (struct lista_t *lst, int item, int pos){
    struct item_t *nodo;
    if (! (item = malloc(sizeof(struct item_t))) )
        return -1; 

    nodo->valor = item;
    nodo->prox = NULL;
    lst->tamanho += 1;

    // se nao houver item na lista
    if (lst->prim == NULL)
    {
        nodo->ant = lst->prim;

        lst->prim = nodo->ant;
        lst->ult = nodo;

        return lst->tamanho;
    }

    struct item_t *aux;
    aux->prox = lst->prim;
    aux->ant = lst;
    // caminha ate achar o fim da lista
    while (aux->prox != NULL)
    {
        aux->ant = aux->prox;
        aux->prox = aux->prox->prox;
    }

    nodo->ant = aux->ant;
    nodo->prox = aux->prox;
    lst->ult = nodo;

    free (aux);
    aux = NULL;

    return lst->tamanho;
}

int lista_retira (struct lista_t *lst, int *item, int pos){
    struct item_t *aux;
    int i = 0;

    if (pos == -1)
    {
        aux = lst->ult;

        lst->ult = lst->ult->ant;

        free (aux);
        aux = NULL;

        lst->tamanho -= 1;

        return lst->tamanho;
    }

    aux->prox = lst->prim;
    aux->ant = lst;
    while (i < pos)
    {
        if (aux->prox->prox == NULL)
            return -1;

        aux->ant = aux->prox;
        aux->prox = aux->prox->prox;
        i++;
    }
    aux->ant->prox = aux->prox->prox;
    aux->prox->prox->ant = aux->ant;

}
