#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fprio.h"
#include "lista.h"
#include "conjunto.h"
#include "estruturas.h"
#include "cria.h"

#include "eventos.h"

int aleat (int min, int max)
{
  return rand() % (max - min + 1) + min;
}

int agenda_evento(struct fprio_t *fila, void *item, int tipo, int prio) {
    return fprio_insere(fila, item, tipo, prio);
}

void *entra(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo,struct fprio_t *lef)
{
    int tpb;
    //calcula TPB = tempo de permanência na base:
    //TPB = 15 + paciência de H * aleatório [1...20]
    tpb = 15 + heroi->paciencia * aleat(1,20);
    //cria e insere na LEF o evento SAI (agora + TPB, H, B)
    agenda_evento(lef,sai((tempo + tpb),heroi,base,mundo,lef),ev_sai,tempo+tpb);

    printf ("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d", tempo, heroi->id, base->id, base->presentes->num, base->lotacao, tempo+tpb);

    return NULL;
}

void *espera(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo,struct fprio_t *lef)
{
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)", tempo, heroi->id, base->id, base->espera->tamanho);
    //adiciona H ao fim da fila de espera B
    lista_insere(base->espera,heroi->id,-1);
    //cria e insere na LEF o evento AVISA(agora,b)
    agenda_evento(lef,avisa(tempo,base,mundo,lef),ev_avisa,tempo);

    return NULL;
}

void *avisa(int tempo, struct base *base,struct mundo *mundo,struct fprio_t *lef)
{
    //enquanto houver vaga em B e houver heróis esperando na fila:
    //retira primeiro herói (H') da fila de B
    //adiciona H' ao conjunto de heróis presentes em B
    //cria e insere na LEF o evento ENTRA (agora, H', B)
    while (base->lotacao > base->presentes->num && base->espera->tamanho > 0)
    {
        int numero,item;
        int temp;
        temp = lista_retira(base->espera,&item,0);
        numero = cjto_insere(base->presentes,item);
        if (!numero)
            return NULL;
        base->presentes++;
        base->espera->tamanho--;
        agenda_evento(lef,entra(tempo,&mundo->herois[temp],base,mundo,lef),ev_entra,tempo);
    }
    return NULL;
}

void *chega(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo,struct fprio_t *lef)
{
    int esperar;
    //mudar onde o heroi se encontra no momento
    heroi->base = base->id;

    if (base->lotacao > base->presentes->num && base->espera->tamanho == 0)
        esperar = 1;
    else
        esperar = (heroi->paciencia) > (10 * base->espera->tamanho);
    
    if (esperar)/*mudar se a lef altera o mundo ou a base*/
    {
        agenda_evento(lef,espera(tempo,heroi,base,mundo,lef),ev_espera,tempo);
        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA", tempo, heroi->id, base->id, base->presentes->num, base->presentes->cap);
    }
    else
    {
        agenda_evento(lef,desiste(tempo,heroi,base,mundo,lef), ev_desiste,tempo);
        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE", tempo, heroi->id, base->id, base->presentes->num, base->presentes->cap);
    }
    return NULL;
}

void *desiste(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo, struct fprio_t *lef)
{
    printf("%6d: DESISTE HEROI %2d BASE %d", tempo, heroi->id, base->id);

    struct base *destino;
    destino = &mundo->bases[aleat(0,mundo->NBases -1)];

    agenda_evento(lef,viaja(tempo,heroi,destino,mundo,lef),ev_viaja,tempo);

    return NULL;
}

void *sai(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo,struct fprio_t *lef)
{
    struct base *nova_base;
    nova_base = &mundo->bases[aleat(0,mundo->NBases -1)];

    cjto_retira(base->presentes,heroi->id);

    agenda_evento(lef,viaja(tempo,heroi,nova_base,mundo,lef),ev_viaja,tempo);

    agenda_evento(lef,avisa(tempo,base,mundo,lef),ev_avisa,tempo);

    //ver tamanho da base
    printf ("%6d: SAI HEROI %2d BASE %d (%2d/%2d)", tempo, heroi->id, base->id, base->presentes->num, base->lotacao);

    return NULL;
}

void *viaja(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo,struct fprio_t *lef)
{
    float distancia,duracao;
    struct base temp = base[heroi->id];
    //calcula duração da viagem:
    //distância = distância cartesiana entre a base atual de H e a base D 
    //d = raiz((x2-x1)quadrado + (y2-y1)quadrado)
    distancia = sqrt((pow(temp.coord_x - base->coord_x,2)) + (pow(temp.coord_y - base->coord_y,2)));

    //duração = distância / velocidade de H
    duracao = distancia / heroi->velocidade;

    printf ("%6d: VIAJA HEROI %2d BASE %2d BASE %d DIST %f VEL %d CHEGA %f", tempo, heroi->id, heroi->base, base->id, distancia, heroi->velocidade, tempo+duracao);
    //cria e insere na LEF o evento CHEGA (agora + duração, H, D)
    agenda_evento(lef,chega((tempo + duracao),heroi,base,mundo,lef),ev_chega,tempo);


    return NULL;
}

void *morre(int tempo, struct heroi *heroi, struct base *base,struct missao *missao,struct mundo *mundo, struct fprio_t *lef)
{
    //retira H do conjunto de heróis presentes em B
    cjto_retira(base->presentes,heroi->id);//mudar numero
    //muda o status de H para morto 
    heroi->vivo = 0;
    //cria e insere na LEF o evento AVISA (agora, B)
    agenda_evento(lef,avisa(tempo,base,mundo,lef),ev_avisa,tempo);

    printf ("%6d: MORRE HEROI %2d MISSAO %d", tempo, heroi->id, missao->id);

    return NULL;
}

// int compara_distancia(const void *a, const void *b)
// {
//   return (*(int*)a-*(int*)b);
// }

//missao
// void *missao(int tempo,struct mundo *mundo, struct missao *missao)
// {
//     struct missao *temp_missao = missao;
//     int possivel = 0;
//     base_t *vet_bases_ordenado[mundo->NBases] ;
//     vet_bases_ordenado[mundo->NBases] = mundo->bases;



//     struct cjto_t uniao_habilidades;

//     float distancia;
//     //guarda as distancias de cada base ate a missaso
//     // for (int i = 0; i < mundo->NBases; i++)
//     // {
//     //     distancia = sqrt((pow(mundo->missoes->coord_x - temp_missao->coord_x,2) + (pow(mundo->missoes->coord_y - temp_missao->coord_y,2))));
//     //     vet_bases_ordenado[i] = mundo->bases[i];
//     // }

//     return NULL;
// }
// //fim
void *fim(int tempo)
{
    /*encerra a simulação
    apresenta estatísticas dos heróis
    apresenta estatísticas das bases
    apresenta estatísticas das missões*/
    tempo += 0;

    return NULL;
}