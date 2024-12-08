#ifndef ESTRUTURAS
#define ESTRUTURAS
#include "conjunto.h"

struct base_distancias
{
    int id;
    float distancia;
};

struct evento
{
    struct base *base;
    struct heroi *heroi;
};

//Espera: fila onde os heróis esperam para poder entrar na base
typedef struct base
{
    int id;
    int lotacao;
    struct cjto_t *presentes;
    struct lista_t *espera;
    int coord_x,coord_y;
} base_t;
//Habilidades: conjunto de habilidades necessárias para cumprir a missão
struct missao
{
    int id;
    struct cjto_t *habilidades;
    int perigo;
    int coord_x,coord_y;
    int realizda;
};

struct heroi
{
    int id;
    struct cjto_t *Habilidades;
    int paciencia;
    int velocidade;
    int experiencia;
    int base;
    int vivo;
};

struct mundo
{
    int NHerois;
    struct heroi herois[50];
    int NBases;
    struct base bases[10];
    int NMissoes;
    struct missao missoes[1000 / 100];
    int NHablidades;
};

#endif