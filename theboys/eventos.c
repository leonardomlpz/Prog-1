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
//estrutura de itens para usar na lef/switch case
struct evento *itens(struct base *base, struct heroi *heroi)
{
    struct evento *elementos;
    if (! (elementos = malloc(sizeof(struct evento))) )
        return NULL;

    elementos->base = base;
    elementos->heroi = heroi;

    return elementos;
}

void entra(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef)
{
    int tpb;
    //calcula tpb = tempo de permanência na base:
    tpb = 15 + heroi->paciencia * aleat(1,20);
    //cria e insere na LEF o evento SAI (agora + TPB, H, B)
    printf ("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, heroi->id, base->id, base->presentes->num, base->lotacao, tempo+tpb);

    base->presentes->num++;

    struct evento *temp;
    temp = itens(base,heroi);
    fprio_insere(lef,temp,ev_sai,tempo + tpb);

    return;
}

void espera(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef)
{
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, heroi->id, base->id, base->espera->tamanho);
    //adiciona H ao fim da fila de espera B
    lista_insere(base->espera,heroi->id,-1);

    //cria e insere na LEF o evento AVISA(agora,b)
    struct evento *temp;
    temp = itens(base,heroi);
    fprio_insere(lef,temp,ev_avisa,tempo);
    return;
}

void avisa(int tempo, struct heroi *heroi,struct base *base,struct fprio_t *lef)
{
    struct evento *temp;
    
    while (base->lotacao > base->presentes->num && base->espera->tamanho > 0)
    {
        int numero,item;
        lista_retira(base->espera,&item,0);
        numero = cjto_insere(base->presentes,item);
        if (numero == -1)
            return;
        base->presentes->num++;
        base->espera->tamanho--;

        temp = itens(base,heroi);
        fprio_insere(lef,temp,ev_entra,tempo);
    }
    return;
}

void chega(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef)
{
    struct evento *temp;
    temp = itens(base,heroi);
    
    int esperar;
    
    heroi->base = base->id;

    if (base->espera->tamanho == 0 || base->lotacao > base->presentes->num)
        esperar = 1;
    else
        esperar = (heroi->paciencia) > (10 * base->espera->tamanho);
    
    if (esperar == 1)
    {
        fprio_insere(lef,temp,ev_espera,tempo);

        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", tempo, heroi->id, base->id, base->presentes->num, base->presentes->cap);
    }
    else
    {
        fprio_insere(lef,temp,ev_desiste,tempo);

        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n", tempo, heroi->id, base->id, base->presentes->num, base->presentes->cap);
    }
    return;
}

void desiste(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo, struct fprio_t *lef)
{
    printf("%6d: DESISTE HEROI %2d BASE %d\n", tempo, heroi->id, base->id);
    //escolhe um destino aleatorio
    struct base *destino;
    destino = &mundo->bases[aleat(0,mundo->NBases -1)];

    struct evento *temp;
    temp = itens(destino,heroi);
    fprio_insere(lef,temp,ev_viaja,tempo);

    return;
}

void sai(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo,struct fprio_t *lef)
{
    //escolhe uma nova base aleatoria
    struct base *nova_base;
    nova_base = &mundo->bases[aleat(0,mundo->NBases -1)];

    cjto_retira(base->presentes,heroi->id);
    base->lotacao--;

    struct evento *temp;
    temp = itens(nova_base,heroi);
    fprio_insere(lef,temp,ev_viaja,tempo);

    temp = itens(base,heroi);
    fprio_insere(lef,temp,ev_avisa,tempo);

    printf ("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", tempo, heroi->id, base->id, base->presentes->num, base->lotacao);

    return;
}

void viaja(int tempo, struct heroi *heroi, struct base *base, struct mundo *mundo, struct fprio_t *lef) {
    //base de origem do heroi
    struct base origem = mundo->bases[heroi->base];

    //calcula a distância entre a base de origem e a base de destino
    float distancia = sqrt(pow(origem.coord_x - base->coord_x, 2) + pow(origem.coord_y - base->coord_y, 2));
    
    //calcular a duração da viagem
    float duracao = distancia / heroi->velocidade;
    
    if (duracao < 0) {
        return;
    }

    printf("%6d: VIAJA HEROI %2d BASE %2d BASE %2d DIST %.2f VEL %d CHEGA %.2f\n", 
           tempo, heroi->id, heroi->base, base->id, distancia, heroi->velocidade, tempo + duracao);

    struct evento *temporario = itens(base, heroi);

    fprio_insere(lef, temporario, ev_chega, tempo + duracao);

    return;
}


void morre(int tempo, struct heroi *heroi, struct base *base,struct missao *missao, struct fprio_t *lef)
{
    

    //retira H do conjunto de heróis presentes em B
    cjto_retira(base->presentes,heroi->id);
    //muda o status de H para morto 
    heroi->vivo = 0;
    //cria e insere na LEF o evento AVISA (agora, B)
    struct evento *temp;
    temp = itens(base,heroi);
    fprio_insere(lef,temp,ev_morre,tempo);

    printf ("%6d: MORRE HEROI %2d MISSAO %d\n", tempo, heroi->id, missao->id);

    return;
}
/*
void bubbleSort(struct base_distancias vetor[], int tamanho) {
    int i, j;
    struct base_distancias temp;
    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j].distancia > vetor[j + 1].distancia) {
                // Troca os elementos se estiverem na ordem errada
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

int misssao(int tempo,struct mundo *mundo, struct missao *missao)
{
    float distancia,risco;

    //vetor de distancia de cada base ate a missao
    struct base_distancias vet_bases_ordenadas[mundo->NBases];

    for (int i = 0; i < mundo->NBases; i++)
    {
        distancia = sqrt((pow(missao->coord_x - mundo->bases[i].coord_x,2) + (pow(missao->coord_y - mundo->bases[i].coord_y,2))));
        vet_bases_ordenadas[i].distancia = distancia;
        vet_bases_ordenadas[i].id = mundo->bases[i].id;
    }
    //ordena o vetor com base nas distancias
    bubbleSort(vet_bases_ordenadas,mundo->NBases);

    struct cjto_t *herois;

    for (int i = 0; i < mundo->NBases; i++)
        //BMP
        if (cjto_contem((mundo->bases[vet_bases_ordenadas[i].id].presentes),missao->habilidades))
        {
            missao->realizda = 1;

            herois = mundo->bases[vet_bases_ordenadas->id].presentes;
            //anda dentro da base bmp
            for (int i = 0; i < mundo->bases[vet_bases_ordenadas[i].id].lotacao; i++)
            {
                
            }

            
        }
}
*/

// void fim(int tempo)
// {
    // 
    // return;
// }