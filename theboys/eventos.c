#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"
#include "lista.h"
#include "conjunto.h"
#include "estruturas.h"
#include "cria.h"

int aleat (long min, long max)
{
  return rand() % (max - min + 1) + min;
}

void *chega(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef)
{
    int esperar;
    //mudar onde o heroi se encontra no momento
    heroi->base = base->id;

    if (base->lotacao > base->presentes->num && base->espera->tamanho == 0)
        esperar = 1;
    else
        esperar = (heroi->paciencia) > (10 * base->espera->tamanho);
    
    if (esperar)/*mudar se a lef altera o mundo ou a base*/
        fprio_insere(lef,espera(tempo,heroi,base,lef),ev_espera,tempo);
    else
        fprio_insere(lef,desiste(tempo,heroi,base,lef),
        ev_desiste,tempo);
}

void *espera(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef)
{
    //adiciona H ao fim da fila de espera B
    lista_insere(base->espera,heroi,-1);
    //cria e insere na LEF o evento AVISA(agora,b)
    fprio_insere(lef,avisa(tempo,base,lef),ev_avisa,tempo);
}

void *desiste(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef)
{
    int destino;
    destino = aleat(1,1);//mudar para base aleatoria
    //cria e insere na LEF o evento VIAJA (agora, H, D)
    //destino aleatorio
    fprio_insere(lef,viaja(tempo,heroi,destino,lef),ev_viaja,tempo);
}

void *avisa(int tempo, struct base *base,struct fprio_t *lef)
{
    //enquanto houver vaga em B e houver heróis esperando na fila:
    //retira primeiro herói (H') da fila de B
    //adiciona H' ao conjunto de heróis presentes em B
    //cria e insere na LEF o evento ENTRA (agora, H', B)
    while (base->lotacao > base->presentes->num && base->espera->tamanho > 0)
    {
        int numero;
        void *temp;
        temp = fprio_retira(base->espera,1,1);
        numero = cjto_insere(base->presentes,temp);
        if (!numero)
            return;
        base->presentes++;
        base->espera->tamanho--;
        fprio_insere(lef,entra(tempo,temp,base,lef),ev_entra,tempo);
    }
}

void *entra(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef)
{
    int tpb;
    //calcula TPB = tempo de permanência na base:
    //TPB = 15 + paciência de H * aleatório [1...20]
    tpb = 15 + heroi->paciencia * aleat(1,20);
    //cria e insere na LEF o evento SAI (agora + TPB, H, B)
    fprio_insere(lef,sai((tempo + tpb),heroi,base,lef),ev_sai,tempo);
}

void *sai(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef)
{
    int *nova_base;
    //retira H do conjunto de heróis presentes em B
    cjto_retira(base->presentes,1);//mudar o numero do cjto
    //escolhe uma base destino D aleatória
    nova_base = aleat(0,10);//mudar dois
    //cria e insere na LEF o evento VIAJA (agora, H, D)
    fprio_insere(lef,viaja(tempo,heroi,nova_base,lef),ev_viaja,tempo);
    //cria e insere na LEF o evento AVISA (agora, B)
    fprio_insere(lef,avisa(tempo,base,lef),ev_avisa,tempo);
}

void *viaja(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef)
{
    float distancia,duracao;
    struct base temp = base[heroi->id];
    //calcula duração da viagem:
    //distância = distância cartesiana entre a base atual de H e a base D 
    //d = raiz((x2-x1)quadrado + (y2-y1)quadrado)
    distancia = sqrt((power(temp.coord_x - base->coord_x)) + (power(temp.coord_y - base->coord_y)));
    //duração = distância / velocidade de H
    duracao = distancia / heroi->velocidade;
    //cria e insere na LEF o evento CHEGA (agora + duração, H, D)
    fprio_insere(lef,chega((tempo + duracao),heroi,base,lef),ev_chega,tempo);
}

void *morre(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef)
{
    //retira H do conjunto de heróis presentes em B
    cjto_retira(base->presentes,0);//mudar numero
    //muda o status de H para morto 
    
    //cria e insere na LEF o evento AVISA (agora, B)
    fprio_insere(lef,avisa(tempo,base,lef),ev_avisa,tempo);
}

//missao
void *missao(int tempo,struct mundo *mundo, struct missao *missao)
{
    struct missao *temp_missao = missao;
    
    float distancia;
    for (int i = 0; i < mundo->NBases; i++)
    {
    distancia = sqrt((pow(mundo->missoes->coord_x - temp_missao->coord_x) + (pow(mundo->missoes->coord_y - temp_missao->coord_y))));
    
    }
}
//fim
void *fim(int tempo)
{
    /*encerra a simulação
    apresenta estatísticas dos heróis
    apresenta estatísticas das bases
    apresenta estatísticas das missões*/
}