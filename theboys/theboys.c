// programa principal do projeto "The Boys - 2024/2"
// Autor: xxxxx, GRR xxxxxx

// seus #includes vão aqui
#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"
#include "lista.h"
#include "conjunto.h"
#include "estruturas.h"
// seus #defines vão aqui

// minimize o uso de variáveis globais

// programa principal
int main ()
{
    // iniciar o mundo
    struct mundo mundo;
    //tempo final do programa
    mundo.Relogio = 1000;
    //tempo final=525600
    mundo.TamMundo;//mudar para alterar tamanho
    mundo.NHablidades = 10;
    mundo.NHerois = mundo.NHablidades * 5;
    mundo.NBases = mundo.NHerois / 5;
    mundo.NMissoes = 0;
    //tempo da simulacao
    int relogio = 0;

  
    // executar o laço de simulação
    do
    {
        
    } while (relogio < mundo.Relogio);
    

    // destruir o mundo

    return (0) ;
}

