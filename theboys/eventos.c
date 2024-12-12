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
struct evento *itens(struct base *base, struct heroi *heroi, missao_t *missao)
{
    struct evento *elementos;
    if (! (elementos = malloc(sizeof(struct evento))) )
        return NULL;

    elementos->base = base;
    elementos->heroi = heroi;
    elementos->missao = missao;

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

    //adicao das hab do heroi ao cjto da base
    struct cjto_t *temporaria;
    temporaria = cjto_uniao(base->hab_presentes,heroi->Habilidades);
    //apaga cjto antigo
    cjto_destroi(base->hab_presentes);
    //base recebe novo conjunto com habilidades atualizadas
    base->hab_presentes = temporaria;//TESTAR SE O PONTEIRO AINDA RECEBE ALGO

    struct evento *temp;
    temp = itens(base,heroi,NULL);
    fprio_insere(lef,temp,ev_sai,tempo + tpb);

    return;
}

void espera(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef)
{
    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, heroi->id, base->id, base->espera->tamanho);
    //adiciona H ao fim da fila de espera B
    lista_insere(base->espera,heroi->id,0);

    //cria e insere na LEF o evento AVISA(agora,b)
    struct evento *temp;
    temp = itens(base,heroi,NULL);
    fprio_insere(lef,temp,ev_avisa,tempo);
    return;
}

void avisa(int tempo, struct heroi *heroi,struct base *base,struct fprio_t *lef)
{
    if (heroi->vivo == 0)
        return;

    struct evento *temp;
    
    printf ("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA [ ", tempo, base->id, base->presentes->num, base->lotacao);
    lista_imprime(base->espera);
    printf (" ]\n");

    while (base->lotacao > base->presentes->num && base->espera->tamanho > 0)
    {
        int numero,item;
        lista_retira(base->espera,&item,0);
        numero = cjto_insere(base->presentes,item);
        if (numero == -1)
            return;
        base->presentes->num++;
        base->espera->tamanho--;

        temp = itens(base,heroi,NULL);
        fprio_insere(lef,temp,ev_entra,tempo);

        printf ("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", tempo, base->id, heroi->id);
    }
    return;
}

void chega(int tempo, struct heroi *heroi, struct base *base,struct fprio_t *lef)
{
    struct evento *temp;
    temp = itens(base,heroi,NULL);
    
    int esperar;
    
    heroi->base = base->id;

    if (base->espera->tamanho == 0 && base->lotacao > base->presentes->num)
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
    temp = itens(destino,heroi,NULL);
    fprio_insere(lef,temp,ev_viaja,tempo);

    return;
}

void sai(int tempo, struct heroi *heroi, struct base *base,struct mundo *mundo,struct fprio_t *lef)
{
    //escolhe uma nova base aleatoria
    struct base *nova_base;
    nova_base = &mundo->bases[aleat(0,9)];//mundo->NBases -1

    base->presentes->num = cjto_retira(base->presentes,heroi->id);

    //remove habilidades do heroi da base
    struct cjto_t *temporario;
    temporario = cjto_dif(base->hab_presentes,heroi->Habilidades);
    cjto_destroi(base->hab_presentes);
    base->hab_presentes = temporario;


    struct evento *temp;
    temp = itens(nova_base,heroi,NULL);
    fprio_insere(lef,temp,ev_viaja,tempo);

    temp = itens(base,heroi,NULL);
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

    struct evento *temporario = itens(base, heroi,NULL);

    fprio_insere(lef, temporario, ev_chega, tempo + duracao);

    return;
}


void morre(int tempo, struct heroi *heroi, struct base *base,struct missao *missao, struct fprio_t *lef)
{

    //retira H do conjunto de heróis presentes em B
    cjto_retira(base->presentes,heroi->id);
    
    base->presentes = cjto_dif(base->presentes,heroi->Habilidades);//testar vazamentos

    //muda o status de H para morto 
    heroi->vivo = 0;
    //cria e insere na LEF o evento AVISA (agora, B)
    struct evento *temp;
    temp = itens(base,heroi,missao);
    fprio_insere(lef,temp,ev_avisa,tempo);

    printf ("%6d: MORRE HEROI %2d MISSAO %d\n", tempo, heroi->id, missao->id);

    return;
}

void bubbleSort(base_t vetor[], int tamanho) {
    int i, j;
    base_t temp;
    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - i - 1; j++) {
            if (vetor[j].distancia_missao > vetor[j + 1].distancia_missao) {
                // Troca os elementos se estiverem na ordem errada
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

//retorna o numero da base se existir
//retorna -1 se nao existir base capaz de cumprir a missao
int bmp(mundo_t *mundo, missao_t *missao)
{
    float distancia;

    for (int i = 0; i < mundo->NBases; i++)
    {
        distancia = sqrt((pow(missao->coord_x - mundo->bases[i].coord_x,2) + (pow(missao->coord_y - mundo->bases[i].coord_y,2))));
        mundo->bases[i].distancia_missao = distancia;
    }

    bubbleSort(mundo->bases,mundo->NBases);
    int pode_ser_realizada = -1;
    for (int i = 0; i < mundo->NBases; i++)
    {
        if (cjto_contem(missao->habilidades,mundo->bases[i].hab_presentes) == 1)
        {
            pode_ser_realizada = mundo->bases[i].id;
            break;
        }
    }

    return pode_ser_realizada;
}

void missao(int tempo, mundo_t *mundo, missao_t *missao, struct fprio_t *lef)
{
    evento_t *temporario;
    float risco;
    int indice;
    indice = bmp(mundo,missao);
    //se o retorno for diferente de -1 pode ser realizada
    if (indice != -1)
    {
        missao->realizda = 1;
        mundo->missoes_realizadas++;

        for (int i = 0; i < mundo->NHerois; i++)
        {
            //testa se o heroi esta na base
            if (mundo->herois[i].base == mundo->bases[indice].id)
            {
                risco = missao->perigo / (mundo->herois[i].paciencia + mundo->herois[indice].experiencia + 1.0);
                if (risco > (aleat(0,30)))
                {
                    temporario = itens(&mundo->bases[indice],&mundo->herois[i],missao);
                    fprio_insere(lef,temporario,ev_morre,tempo);
                    mundo->NHerois_mortos++;
                }
                else
                    mundo->herois[i].experiencia++;
            }
        }
    }
    else
    {
        //passa como NULL os parametros pois nao sao usados na missao
        temporario = itens(NULL,NULL,missao);
        fprio_insere(lef,temporario,ev_missao,tempo + 24*60);
    }
}

void fim(mundo_t *mundo)
{
    for (int i = 0; i < mundo->NHerois; i++)
    {
        if (mundo->herois[i].vivo == 1)
        {
            printf ("HEROI %2d VIVO  PAC %3d VEL %4d EXP %4d HABS [ ", i, mundo->herois[i].paciencia, mundo->herois[i].velocidade, mundo->herois[i].experiencia);
            cjto_imprime(mundo->herois[i].Habilidades);
            printf (" ]\n");
        }
        else
        {
            printf ("HEROI %2d MORTO  PAC %3d VEL %4d EXP %4d HABS [ ", i, mundo->herois[i].paciencia, mundo->herois[i].velocidade, mundo->herois[i].experiencia);
            cjto_imprime(mundo->herois[i].Habilidades);
            printf (" ]\n");
        }
    }

    for (int i = 0; i < mundo->NBases; i++)
    {
        printf ("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n", mundo->bases[i].id, mundo->bases[i].lotacao, mundo->bases[i].qtde_max_fila, mundo->bases[i].missoes_participadas);
    }

    printf ("EVENTOS TRATADOS: %d\n", mundo->missoes_realizadas);

    float porcentagem;
    porcentagem = (mundo->missoes_realizadas/mundo->missoes_total)*100;
    
    printf ("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", mundo->missoes_realizadas, mundo->missoes_total, porcentagem);

    porcentagem = (mundo->tentativas_min + mundo->tentativas_max)/2;
    printf ("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", mundo->tentativas_min, mundo->tentativas_max, porcentagem);

    porcentagem = (mundo->NHerois_mortos/mundo->NHerois)*100;
    printf ("TAXA MORTALIDADE: %.1f%%\n", porcentagem);

    return;
}