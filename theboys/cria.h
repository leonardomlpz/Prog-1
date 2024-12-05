#ifndef CRIA
#define CRIA

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

void cria_missao(struct mundo *mundo);

void cria_base(struct mundo *mundo);

#endif