#ifndef ESTRUTURAS
#define ESTRUTURAS
#include "conjunto.h"

typedef struct base_distancias
{
    int id;
    float distancia;
}base_dist;

//Espera: fila onde os heróis esperam para poder entrar na base
typedef struct base
{
    int id;
    int lotacao;
    struct cjto_t *presentes;
    struct lista_t *espera;
    int coord_x,coord_y;
    struct cjto_t *hab_presentes;
    int missoes_participadas;
    int qtde_max_fila;
    float distancia_missao;
} base_t;
//Habilidades: conjunto de habilidades necessárias para cumprir a missão
typedef struct missao
{
    int id;
    struct cjto_t *habilidades;
    int perigo;
    int coord_x,coord_y;
    int realizda;
    int tentativas;
}missao_t;

typedef struct evento
{
    struct base *base;
    struct heroi *heroi;
    missao_t *missao;
}evento_t;

typedef struct heroi
{
    int id;
    struct cjto_t *Habilidades;
    int paciencia;
    int velocidade;
    int experiencia;
    int base;
    int vivo;
}heroi_t;

typedef struct mundo
{
    int NHerois;
    struct heroi herois[50];
    int NBases;
    struct base bases[10];
    int NMissoes;
    struct missao missoes[1000 / 100];
    int NHablidades;
    int missoes_realizadas;
    int missoes_total;
    base_dist bases_ordenadas[10];
    int tentativas_min,tentativas_max;
    int NHerois_mortos;
}mundo_t;

#endif