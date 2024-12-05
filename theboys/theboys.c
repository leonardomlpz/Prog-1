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
    int relogio = 0;

    cria_base(mundo);
    cria_herois(mundo);
    cria_missao(mundo);

    for (int i = 0; i < mundo->NHerois;i++)
    {
        int base_temporaria = aleat(0,mundo->NBases -1);
        int tempo_aleatorio = aleat(0,4320);
        fprio_insere(lef,chega(tempo_aleatorio, &mundo->herois[i], base_temporaria, lef),1,tempo_aleatorio);
    }

    for (int i = 0; i < mundo->NHerois;i++)
    {
        int tempo_aleatorio = aleat(0,T_FIM);
        
    }

    void *evento = fprio_retira(lef,1,1);
    // executar o laço de simulação
    do
    {
        switch (((struct fpnodo_t *)evento)->tipo)
        {
            case 1:  // Chegada
            chega(relogio, ((struct fpnodo_t *)evento), ((struct fpnodo_t *)evento)->base, lef);
        break;
                
        case 2:  // Espera
            espera(relogio, ((struct fpnodo_t *)evento)->heroi, ((struct fpnodo_t *)evento)->base, lef);
            break;

        case 3:  // Desiste
            desiste(relogio, ((struct fpnodo_t *)evento)->heroi, ((struct fpnodo_t *)evento)->base, lef);
            break;

        case 4:  // Viaja
            viaja(relogio, ((struct fpnodo_t *)evento)->heroi, ((struct fpnodo_t *)evento)->base, lef);
            break;

        case 5:  // Entra
            entra(relogio, ((struct fpnodo_t *)evento)->heroi, ((struct fpnodo_t *)evento)->base, lef);
            break;

        case 6:  // Sai
            sai(relogio, ((struct fpnodo_t *)evento)->heroi, ((struct fpnodo_t *)evento)->base, lef);
            break;

        case 7:  // Avisa
            avisa(relogio, ((struct fpnodo_t *)evento)->base, lef);
            break;

        
        default:
            break;
        }
    } while (relogio < mundo->Relogio);
    

    // destruir o mundo

    return (0) ;
}

