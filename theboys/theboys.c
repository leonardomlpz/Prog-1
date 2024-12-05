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
#define T_FIM 10000
// minimize o uso de variáveis globais
// programa principal
int main ()
{
    int t_inicio = 0;
    int tam_mundo = 20000;
    // iniciar o mundo
    int t_fim_mundo = T_FIM;//mudar para 525600

    struct fprio_t *lef;

    struct mundo *mundo;
    if (! (mundo = malloc(sizeof(struct mundo))) )
        return NULL;

    //tempo final do programa
    mundo->NHablidades = 10;
    mundo->NHerois = mundo->NHablidades * 5;
    mundo->NMissoes = t_fim_mundo / 100;
    //tempo da simulacao
    mundo->Relogio = 0;

    cria_base(mundo);
    cria_herois(mundo);
    cria_missao(mundo);

    for (int i = 0; i < mundo->NHerois;i++)
    {
        int base_temporaria = aleat(0,mundo->NBases -1);
        int tempo_aleatorio = aleat(0,4320);
        fprio_insere(lef,chega(tempo_aleatorio, &mundo->herois[i], base_temporaria, lef),1,tempo_aleatorio);
    }

    for (int i = 0; i < mundo->NMissoes;i++)
    {
        int tempo_aleatorio = aleat(0,T_FIM);
        fprio_insere(lef,missao(tempo_aleatorio,&mundo->missoes[i]),1,tempo_aleatorio);
    }

    fprio_insere(lef,fim(T_FIM),ev_fim,T_FIM);



    int tipo,tempo;

    // executar o laço de simulação
    do
    {
        void *evento = fprio_retira(lef,&tipo,&tempo);
        if (evento == NULL)
            break;

        switch (tipo)
        {
            case ev_chega:
            chega(tempo, ((struct heroi *)evento), ((struct base *)evento), lef);
        break;
                
        case ev_espera:
            espera(tempo, ((struct heroi *)evento), ((struct base *)evento), lef);
            break;

        case ev_desiste:
            desiste(tempo, ((struct heroi *)evento), ((struct base *)evento), lef);
            break;

        case ev_viaja:
            viaja(tempo, ((struct heroi *)evento), ((struct base *)evento), lef);
            break;

        case ev_entra:
            entra(tempo, ((struct heroi *)evento), ((struct base *)evento), lef);
            break;

        case ev_sai:
            sai(tempo, ((struct heroi *)evento), ((struct base *)evento), lef);
            break;

        case ev_avisa:
            avisa(tempo, ((struct base *)evento), lef);
            break;

        
        default:
            break;
        }
    } while (tempo < T_FIM);
    

    // destruir o mundo

    return (0) ;
}

