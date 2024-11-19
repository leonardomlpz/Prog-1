#ifndef ESTRUTURAS
#define ESTRUTURAS
#include "conjunto.h"

struct base
{
    int id;
    int lotacao;
    //presentes
    //espera -> fila para entrar
    //local [x][y]
};

struct missao
{
    int id;
    struct cjto_t habilidades;
    int perigo;
    //local [x][y]
};

struct heroi
{
    int id;
    int Habilidades;
    int paciencia;
    int velocidade;
    int experiencia;
    int *base;
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