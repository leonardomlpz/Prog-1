// programa principal do projeto "The Boys - 2024/2"
// Autor: xxxxx, GRR xxxxxx

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fprio.h"
#include "lista.h"
#include "conjunto.h"
#include "estruturas.h"
#include "eventos.h"
#include "cria.h"
// seus #defines vão aqui

// minimize o uso de variáveis globais
// programa principal
int main ()
{
    srand(0);

    // iniciar o mundo
    int t_fim_mundo = T_FIM;//mudar para 525600

    struct fprio_t *lef;
    if (! (lef = malloc(sizeof(struct fprio_t))) )
        return 0;

    struct mundo *mundo;
    if (! (mundo = malloc(sizeof(struct mundo))) )
        return 0;

    //tempo final do programa
    mundo->NHablidades = 10;
    mundo->NHerois = mundo->NHablidades * 5;
    mundo->NMissoes = t_fim_mundo / 100;
    //tempo da simulacao
    mundo->Relogio = 0;
    mundo->NBases = mundo->NHerois / 5;
    mundo->TamMundo_x = 10000;
    mundo->TamMundo_y = 10000;

    //cria_base(mundo);
    cria_base(mundo);
    cria_herois(mundo);
    inicia_herois(mundo,lef);
    
    //cria_missao(mundo);
    // inicializa herois
    for (int i = 0; i < mundo->NHerois;i++)
    {
        int base_temporaria = aleat(0,mundo->NBases -1);
        int tempo_aleatorio = aleat(0,4320);

        struct evento *temp;
        temp = itens(&mundo->bases[base_temporaria],&mundo->herois[i]);
        fprio_insere(lef,temp,ev_chega,tempo_aleatorio);
    }
    // inicializa missoes


    int tipo,tempo = 0;
    struct evento *ev;

    // executar o laço de simulação
    while (tempo < T_FIM)
    {
        ev = fprio_retira(lef,&tipo,&tempo);
        if (ev == NULL)
            break;

        switch (tipo)
        {
            case ev_chega:
            chega(tempo, ev->heroi, ev->base, lef);
            break;
                
        case ev_espera:
            espera(tempo, ev->heroi, ev->base, lef);
            break;

        case ev_desiste:
            desiste(tempo, ev->heroi, ev->base, mundo, lef);
            break;

        case ev_viaja:
            viaja(tempo, ev->heroi, ev->base, mundo, lef);
            break;

        case ev_entra:
            entra(tempo, ev->heroi, ev->base, lef);
            break;

        case ev_sai:
            sai(tempo, ev->heroi, ev->base, mundo, lef);
            break;

        case ev_avisa:
            avisa(tempo, ev->heroi, ev->base, lef);
            break;

        
        default:
            break;
        }
    }
    

    // destruir o mundo

    return (0) ;
}

