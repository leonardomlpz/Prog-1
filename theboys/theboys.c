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
int t_inicio = 0;
int tam_mundo = 20000;
// programa principal
int main ()
{
    // iniciar o mundo
    int t_fim_mundo = 10000;//mudar para 525600

    struct fprio_t *lef;

    struct mundo mundo;
    //tempo final do programa
    mundo.NHablidades = 10;
    mundo.NHerois = mundo.NHablidades * 5;
    mundo.NMissoes = t_fim_mundo / 100;
    //tempo da simulacao
    int relogio = 0;

  
    // executar o laço de simulação
    do
    {
        switch (lef->prim->tipo)
        {
        case 1:
            chega;
            break;
        
        default:
            break;
        }
    } while (relogio < mundo.Relogio);
    

    // destruir o mundo

    return (0) ;
}

