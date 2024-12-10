#ifndef EVENTOS
#define EVENTOS

int aleat (int min, int max);

int agenda_evento(struct fprio_t *fila, void *item, int tipo, int prio);

evento_t *itens(base_t *base, heroi_t *heroi);

void chega(int tempo, heroi_t *heroi, base_t *base,struct fprio_t *lef);

void espera(int tempo, heroi_t *heroi, base_t *base,struct fprio_t *lef);

void desiste(int tempo, heroi_t *heroi, base_t *base,mundo_t *mundo,struct fprio_t *lef);

void avisa(int tempo, heroi_t *heroi,base_t *base,struct fprio_t *lef);

void entra(int tempo, heroi_t *heroi, base_t *base,struct fprio_t *lef);

void sai(int tempo, heroi_t *heroi, base_t *base,mundo_t *mundo,struct fprio_t *lef);

void viaja(int tempo, heroi_t *heroi, base_t *base,mundo_t *mundo,struct fprio_t *lef);

void morre(int tempo, heroi_t *heroi, base_t *base,struct missao *missao, struct fprio_t *lef);

void missao(int tempo,mundo_t *mundo, struct missao *missao, struct fprio_t *lef);

void fim(int tempo, mundo_t *mundo);

#endif