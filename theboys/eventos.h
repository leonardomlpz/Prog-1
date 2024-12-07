#ifndef EVENTOS
#define EVENTOS

int aleat (int min, int max);

int agenda_evento(struct fprio_t *fila, void *item, int tipo, int prio);

void *chega(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo,struct fprio_t *lef);

void *espera(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo,struct fprio_t *lef);

void *desiste(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo,struct fprio_t *lef);

void *avisa(int tempo, struct base *base,struct mundo *mundo,struct fprio_t *lef);

void *entra(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo,struct fprio_t *lef);

void *sai(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo,struct fprio_t *lef);

void *viaja(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo,struct fprio_t *lef);

void *morre(int tempo, struct heroi *heroi, struct base *base,struct missao *missao,struct mundo *mundo, struct fprio_t *lef);

void *missao(int tempo,struct mundo *mundo, struct missao *missao);

void *fim(int tempo);

#endif