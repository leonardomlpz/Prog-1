#ifndef ESTRUTURAS
#define ESTRUTURAS
#include "conjunto.h"
//Espera: fila onde os heróis esperam para poder entrar na base
struct base
{
    int id;
    int lotacao;
    struct cjto_t *presentes;
    struct fprio_t *espera;
    int coord_x,coord_y;
};
//Habilidades: conjunto de habilidades necessárias para cumprir a missão
struct missao
{
    int id;
    struct cjto_t habilidades;
    int perigo;
    int coord_x,coord_y;
};

struct heroi
{
    int id;
    int Habilidades;
    int paciencia;
    int velocidade;
    int experiencia;
    int base;
};

struct mundo
{
    int NHerois;
    int *herois;
    int NBases;
    int *bases;
    int NMissoes;
    int *missoes;
    int NHablidades;
    int TamMundo[5][5];//mudar tamanho depois
    int Relogio;
};

#endif