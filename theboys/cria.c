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
        temp.Habilidades = cjto_aleat(mundo->NHablidades,4);//alterar o 1
        temp.vivo = 1;

        mundo->herois[i] = temp;
    }
    return;
}

void inicia_herois(struct mundo *mundo, struct fprio_t *lef)
{
    struct heroi temp;
    int tempo;
    for (int i = 0; i < mundo->NHerois; i++)
    {
        temp = mundo->herois[i];
        temp.base = aleat(0,mundo->NBases -1);

        mundo->herois[i] = temp;
        tempo = aleat(0,4320);

        struct evento *temp;
        temp = itens(&mundo->bases[i],&mundo->herois[i]);
        fprio_insere(lef,temp,ev_chega,tempo);
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
        printf("ID:%2d  LOTACAO:%2d  COORD:%6d", base.id, base.lotacao,base.coord_x);
        base.presentes->num = 0;
        printf("presentes num:%4d\n", base.presentes->num);
        base.espera = lista_cria();

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
        missao.coord_x = aleat(0,mundo->TamMundo_x);//mudar tam mundo
        missao.coord_y = aleat(0,mundo->TamMundo_y);
        missao.habilidades = cjto_aleat(mundo->NHablidades,aleat(6,10));//mudar para [6..10]
        missao.perigo = aleat(0,100);

        mundo->missoes[i] = missao;
    }
    return;
}
