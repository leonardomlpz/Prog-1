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

struct evento *itens(struct base *base, struct heroi *heroi)
{
    struct evento *elementos;
    if (! (elementos = malloc(sizeof(struct evento))) )
        return NULL;

    elementos->base = base;
    elementos->heroi = heroi;

    return elementos;
}

void *entra(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef)
{
    int tpb;
    //calcula TPB = tempo de permanência na base:
    //TPB = 15 + paciência de H * aleatório [1...20]
    tpb = 15 + heroi->paciencia * aleat(1,20);
    //cria e insere na LEF o evento SAI (agora + TPB, H, B)

    base->presentes->num++;

    struct evento *temp;
    temp = itens(base,heroi);
    fprio_insere(lef,temp,ev_sai,tempo + tpb);

    printf ("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, heroi->id, base->id, base->presentes->num, base->lotacao, tempo+tpb);

    return NULL;
}

void *espera(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef)
{
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, heroi->id, base->id, base->espera->tamanho);
    //adiciona H ao fim da fila de espera B
    lista_insere(base->espera,heroi->id,-1);
    //cria e insere na LEF o evento AVISA(agora,b)

    struct evento *temp;
    temp = itens(base,heroi);
    fprio_insere(lef,temp,ev_avisa,tempo);
    return NULL;
}

void *avisa(int tempo, struct heroi *heroi,struct base *base,struct fprio_t *lef)
{
    struct evento *temp;
    temp = itens(base,heroi);
    //enquanto houver vaga em B e houver heróis esperando na fila:
    //retira primeiro herói (H') da fila de B
    //adiciona H' ao conjunto de heróis presentes em B
    //cria e insere na LEF o evento ENTRA (agora, H', B)

    while (base->lotacao > base->presentes->num && base->espera->tamanho > 0)
    {
        int numero,item;
        lista_retira(base->espera,&item,1);
        numero = cjto_insere(base->presentes,item);
        if (!numero)
            return NULL;
        base->presentes->num++;
        base->espera->tamanho--;

        fprio_insere(lef,temp,ev_entra,tempo);
    }
    return NULL;
}

void *chega(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef)
{
    struct evento *temp;
    temp = itens(base,heroi);
    
    int esperar;
    //mudar onde o heroi se encontra no momento
    heroi->base = base->id;

    if (base->espera->tamanho == 0 || base->lotacao > base->presentes->num)
        esperar = 1;
    else
        esperar = (heroi->paciencia) > (10 * base->espera->tamanho);
    
    if (esperar == 1)/*mudar se a lef altera o mundo ou a base*/
    {
        fprio_insere(lef,temp,ev_espera,tempo);

        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", tempo, heroi->id, base->id, base->presentes->num, base->presentes->cap);
    }
    else
    {
        fprio_insere(lef,temp,ev_desiste,tempo);

        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n", tempo, heroi->id, base->id, base->presentes->num, base->presentes->cap);
    }
    return NULL;
}

void *desiste(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo, struct fprio_t *lef)
{
    printf("%6d: DESISTE HEROI %2d BASE %d\n", tempo, heroi->id, base->id);

    struct base *destino;
    destino = &mundo->bases[aleat(0,mundo->NBases -1)];

    struct evento *temp;
    temp = itens(destino,heroi);
    fprio_insere(lef,temp,ev_viaja,tempo);

    return NULL;
}

void *sai(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo,struct fprio_t *lef)
{
    struct base *nova_base;
    nova_base = &mundo->bases[aleat(0,mundo->NBases -1)];

    cjto_retira(base->presentes,heroi->id);

    struct evento *temp;
    temp = itens(nova_base,heroi);
    fprio_insere(lef,temp,ev_viaja,tempo);


    temp = itens(base,heroi);
    fprio_insere(lef,temp,ev_avisa,tempo);

    //ver tamanho da base
    printf ("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", tempo, heroi->id, base->id, base->presentes->num, base->lotacao);

    return NULL;
}

void *viaja(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo,struct fprio_t *lef)
{
    float distancia = 0;
    float duracao = 0;
    struct base temp = mundo->bases[heroi->base];
    //calcula duração da viagem:
    //distância = distância cartesiana entre a base atual de H e a base D 
    //d = raiz((x2-x1)quadrado + (y2-y1)quadrado)
    distancia = sqrt((pow(temp.coord_x - base->coord_x,2)) + (pow(temp.coord_y - base->coord_y,2)));

    //duração = distância / velocidade de H
    duracao = distancia / heroi->velocidade;

    printf ("%6d: VIAJA HEROI %2d BASE %2d BASE %d DIST %.2f VEL %d CHEGA %f\n", tempo, heroi->id, heroi->base, base->id, distancia, heroi->velocidade, tempo+duracao);
    //cria e insere na LEF o evento CHEGA (agora + duração, H, D)
    struct evento *temporario;
    temporario = itens(base,heroi);
    fprio_insere(lef,temporario,ev_chega,tempo + duracao);


    return NULL;
}

void *morre(int tempo, struct heroi *heroi, struct base *base,struct missao *missao, struct fprio_t *lef)
{
    //retira H do conjunto de heróis presentes em B
    cjto_retira(base->presentes,heroi->id);//mudar numero
    //muda o status de H para morto 
    heroi->vivo = 0;
    //cria e insere na LEF o evento AVISA (agora, B)
    struct evento *temp;
    temp = itens(base,heroi);
    fprio_insere(lef,temp,ev_morre,tempo);

    printf ("%6d: MORRE HEROI %2d MISSAO %d\n", tempo, heroi->id, missao->id);

    return NULL;
}

// int compara_distancia(const void *a, const void *b)
// {
//   return (*(int*)a-*(int*)b);
// }
// int misssao(int tempo,struct mundo *mundo, struct missao *missao)
// {
//    cria uma copia das bases para ordenar com base nas distancias da missao
//   struct base base_ordenada[10];
//      for (int i = 0; i < mundo->NBases; i++)
//          base_ordenada[i] = mundo->bases[i];
// 
// 
// 
// 
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