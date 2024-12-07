// programa principal do projeto "The Boys - 2024/2"
// Autor: xxxxx, GRR xxxxxx

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
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
    mundo->NBases = 50;

    cria_base(mundo);
    cria_herois(mundo);
    //cria_missao(mundo);
    // inicializa herois
    for (int i = 0; i < mundo->NHerois;i++)
    {
        int base_temporaria = aleat(0,mundo->NBases -1);
        int tempo_aleatorio = aleat(0,4320);
        agenda_evento(lef,chega(tempo_aleatorio, &mundo->herois[i], &mundo->bases[base_temporaria], mundo, lef),ev_chega,tempo_aleatorio);
    }
    // inicializa missoes

    agenda_evento(lef,fim(T_FIM),ev_fim,T_FIM);



    int tipo,tempo = 0;
    void *evento;

    // executar o laço de simulação
    while (tempo < T_FIM)
    {
        evento = fprio_retira(lef,&tipo,&tempo);
        if (evento == NULL)
            break;

        switch (tipo)
        {
            case ev_chega:
            chega(tempo, ((struct heroi *)evento), ((struct base *)evento), mundo, lef);
        break;
                
        case ev_espera:
            espera(tempo, ((struct heroi *)evento), ((struct base *)evento), mundo, lef);
            break;

        case ev_desiste:
            desiste(tempo, ((struct heroi *)evento), ((struct base *)evento),mundo,  lef);
            break;

        case ev_viaja:
            viaja(tempo, ((struct heroi *)evento), ((struct base *)evento), mundo, lef);
            break;

        case ev_entra:
            entra(tempo, ((struct heroi *)evento), ((struct base *)evento), mundo, lef);
            break;

        case ev_sai:
            sai(tempo, ((struct heroi *)evento), ((struct base *)evento), mundo, lef);
            break;

        case ev_avisa:
            avisa(tempo, ((struct base *)evento), mundo, lef);
            break;

        
        default:
            break;
        }
    }
    

    // destruir o mundo

    return (0) ;
}

