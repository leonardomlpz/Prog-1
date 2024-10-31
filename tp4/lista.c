// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Implementação do TAD - a completar
//
// Implementação com lista encadeada dupla não-circular

#include <stdio.h>
#include <stdlib.h>
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
    struct item_t *aux;
    aux = lst->prim;

    struct item_t *nodo;
    if (! (nodo = malloc(sizeof(struct item_t))) )
        return -1; 

    //insere no fim da lista
    if (pos > lst->tamanho || pos == -1)
    {
        aux = lst->ult;
        aux->prox = nodo;
        nodo->ant = aux;
        lst->ult = nodo;
        lst->tamanho++;

        return lst->tamanho;
    }

    nodo->valor = item;
    nodo->prox = NULL;
    nodo->ant = NULL;
    lst->tamanho += 1;

    // se nao houver item na lista
    if (lst->prim == NULL)
    {
        nodo->ant = NULL;

        lst->prim = nodo;
        lst->ult = nodo;
        nodo->ant = NULL;

        return lst->tamanho;
    }

    //insere na primeira posicao
    if (pos == 0)
    {
        lst->prim = nodo;
        nodo->prox = aux;
        aux->ant = nodo;

        return lst->tamanho;
    }

    //insere no meio
    int contador = 0;
    // anda ate achar a posicao ou acabar a lista
    while (contador < pos)
    {
        contador += 1;
        aux = aux->prox;
    }

    nodo->ant = aux->ant;
    nodo->prox = aux;
    //testa se foi inserido na primeira posicao
    if (nodo->ant == NULL) 
        lst->prim = nodo;
    //testa se foi inserido na ultima posicao
    if (nodo->prox == NULL)
        lst->ult = nodo;

    //movimenta o aux
    aux->ant = nodo;

    free (aux);
    aux = NULL;

    return lst->tamanho;
}

struct lista_t *lista_destroi (struct lista_t *lst){
    struct item_t *aux;
    aux = lst->prim;

    //elimina elementos da lista
    while (aux->prox != NULL)
    {
        aux = aux->prox;

        free (aux->ant);
        aux->ant= NULL;

        if (aux->prox == NULL)
        {
            free (aux);
            aux = NULL;

            return NULL;
        }    
    }

    lst->prim = NULL;
    lst->ult = NULL;
    lst->tamanho = 0;

    free (lst);

    return NULL;
}

int lista_retira (struct lista_t *lst, int *item, int pos){
    struct item_t *aux;
    int cont = 1;

    if (pos == -1)
    {
        aux = lst->ult;

        lst->ult = lst->ult->ant;

        free (aux);
        aux = NULL;

        lst->tamanho -= 1;

        return lst->tamanho;
    }

    aux = lst->prim;
    //caminha ate chegar na posicao para retirar    
    while (cont <= pos)
    {
        if (aux->prox == NULL)
            return -1;

        aux = aux->prox;
        cont++;
    }
    // liga o antetior com o prox pulando o removido
    aux->ant = aux->prox;
    aux->prox->ant = aux->ant;

    *item = aux->valor;

    free (aux);
    aux = NULL;

    lst->tamanho -= 1;

    return lst->tamanho;
}

int lista_consulta (struct lista_t *lst, int *item, int pos){
    struct item_t *aux;

    if ((pos == -1) || pos > (lst->tamanho))
    {
        aux = lst->ult;
        *item = aux->valor;

        aux = NULL;

        return lst->tamanho;
    }

    int cont = 1;
    aux = lst->prim;

    while (cont <= pos)
    {
        if (aux->prox == NULL)
            return -1;

        aux = aux->prox;
        cont++;
    }    

    *item = aux->valor;

    aux = NULL;

    return lst->tamanho;
}

int lista_procura (struct lista_t *lst, int valor){
    struct item_t *aux;
    aux = lst->prim;
    int tam = 1;
    while (tam <= lst->tamanho)
    {
        if (aux->valor == valor)
            return tam;

        aux = aux->prox;
        tam ++;
    }

    return -1;
}

int lista_tamanho (struct lista_t *lst){
    if (lst->tamanho < 0)
        return -1;

    return lst->tamanho;
}

void lista_imprime (struct lista_t *lst){
    struct item_t *aux;
    if (lst->prim == NULL)
        return;

    aux = lst->prim;
    printf ("%d", aux->valor);
    
    for (int i = 2; i <= lst->tamanho; i++)
    {
        aux = aux->prox;
        printf (" %d", aux->valor);
    }
    return;
}