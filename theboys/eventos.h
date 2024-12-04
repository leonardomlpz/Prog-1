#ifndef EVENTOS
#define EVENTOS

int aleat (long min, long max);

void *chega(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef);

void *espera(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef);

void *desiste(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef);

void *avisa(int tempo, struct base *base,struct fprio_t *lef);

void *entra(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef);

void *sai(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef);

void *viaja(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef);

void *morre(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef);

void missao(int tempo,struct missao missao);

void fim(int tempo);

#endif