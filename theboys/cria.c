#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"
#include "lista.h"
#include "conjunto.h"
#include "estruturas.h"
#include "eventos.h"
#include "cria.h"

void cria_herois(struct mundo *mundo)
{
    struct heroi temp;
    for (int i = 0; i < mundo->NHerois; i++)
    {
        temp.id = i;
        temp.experiencia = 0;
        temp.paciencia = aleat(0,100);
        temp.velocidade = aleat(50,5000);
        temp.Habilidades = cjto_aleat(mundo->NHablidades,aleat(1,3));//alterar o 1
        temp.vivo = 1;

        mundo->herois[i] = temp;
    }
    return;
}

void inicia_missoes(mundo_t *mundo, struct fprio_t *lef)
{
    struct evento *temporario;
    int tempo;

    for (int i = 0; i < mundo->NMissoes; i++)
    {
        tempo = aleat(0,T_FIM);

        temporario = itens(&mundo->bases[1],&mundo->herois[1],&mundo->missoes[i]);
        fprio_insere(lef,temporario,ev_missao,tempo);
    }
}

void inicia_herois(struct mundo *mundo, struct fprio_t *lef)
{
    struct heroi temp;
    struct evento *temporario;
    int tempo;
    for (int i = 0; i < mundo->NHerois; i++)
    {
        temp = mundo->herois[i];
        temp.base = aleat(0,mundo->NBases -1);

        mundo->herois[i] = temp;
        tempo = aleat(0,4320);

        //cjto_imprime(mundo->herois[i].Habilidades);printf("\n");///////

        temporario = itens(&mundo->bases[temp.base],&mundo->herois[i],NULL);
        fprio_insere(lef,temporario,ev_chega,tempo);
    }
}

void cria_base(struct mundo *mundo)
{
    struct base base;
    for (int i = 0; i < mundo->NBases; i++)
    {
        base.id = i;
        base.coord_x = aleat(0,TAM_MUNDO);
        base.coord_y = aleat(0,TAM_MUNDO);
        base.lotacao = aleat(3,10);
        base.presentes = cjto_cria(base.lotacao);
        base.presentes->num = 0;
        base.espera = lista_cria();
        base.hab_presentes = cjto_cria(base.lotacao*3);
        base.hab_presentes->num = 0;

        base.distancia_missao = 0;
        base.qtde_max_fila = 0;
        base.missoes_participadas = 0;

        printf("base id:%d esp tam:%d qtde presentes:%d cap:%d\n", base.id, base.espera->tamanho,base.presentes->num,base.presentes->cap);


        mundo->bases[i] = base;
    }

    return;
}

void cria_missao(struct mundo *mundo)
{
    struct missao missao;
    for (int i = 0; i < mundo->NMissoes; i++)
    {
        missao.id = i;
        missao.coord_x = aleat(0,TAM_MUNDO);
        missao.coord_y = aleat(0,TAM_MUNDO);
        missao.habilidades = cjto_aleat(10,aleat(6,10));
        missao.perigo = aleat(0,100);
        missao.tentativas = 0;
        missao.realizda = 0;

        mundo->missoes[i] = missao;
    }
    return;
}

void destroi_mundo(struct mundo *mundo)
{
    //destroi bases
    for (int i = 0; i < mundo->NBases; i++)
    {
        lista_destroi(mundo->bases[i].espera);
        cjto_destroi(mundo->bases[i].presentes);
    }
    
    for (int i = 0; i < mundo->NHerois; i++)
        cjto_destroi(mundo->herois[i].Habilidades);

    return;
}