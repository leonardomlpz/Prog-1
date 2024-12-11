#ifndef CRIA
#define CRIA

#include "estruturas.h"
#include "eventos.h"
#include "fprio.h"

#define T_FIM 2000
#define TAM_MUNDO 20000

#define ev_chega 1
#define ev_espera 2
#define ev_desiste 3
#define ev_viaja 4
#define ev_entra 5
#define ev_sai 6
#define ev_avisa 7
#define ev_morre 8
#define  ev_missao 9
#define ev_fim 10

void cria_herois(struct mundo *mundo);

void inicia_herois(struct mundo *mundo, struct fprio_t *lef);

void cria_missao(struct mundo *mundo);

void inicia_missoes(mundo_t *mundo, struct fprio_t *lef);

void cria_base(struct mundo *mundo);

void destroi_mundo(struct mundo *mundo);

#endif