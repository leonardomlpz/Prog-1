#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"
#include "lista.h"
#include "conjunto.h"
#include "estruturas.h"

void chega(int tempo, struct heroi *heroi, struct base *base)
{
    int espera;
    //mudar onde o heroi se encontra no momento
    heroi->base = base->id;

    if (base->lotacao > base->presentes->num && base->espera->num == 0)
    {
        //completar
    }
}

void espera(int tempo, struct heroi *heroi, struct base *base)
{
    //adiciona H ao fim da fila de espera B
    fprio_insere(base->espera,heroi,1,1);
    //cria e insere na LEF o evento AVISA(agora,b)
    avisa(tempo,base);
}

void desiste(int tempo, struct heroi *heroi, struct base *base)
{
    int destino;
    destino;//recebe num aleatorio de base
    //escolhe uma base destino D aleatória
    //cria e insere na LEF o evento VIAJA (agora, H, D)
    //destino aleatorio
    viaja(tempo,heroi,destino);
}

void avisa(int tempo, struct base *base)
{
    //enquanto houver vaga em B e houver heróis esperando na fila:
    //retira primeiro herói (H') da fila de B
    //adiciona H' ao conjunto de heróis presentes em B
    //cria e insere na LEF o evento ENTRA (agora, H', B)
    while (base->lotacao > base->presentes->num && base->espera->num > 0)
    {
        int numero;
        void *temp;
        temp = fprio_retira(base->espera,1,1);
        numero = cjto_insere(base->presentes,temp);
        if (!numero)
            return;
        base->presentes++;
        base->espera->num--;
    }
}

void entra(int tempo, struct heroi *heroi, struct base *base)
{
    //calcula TPB = tempo de permanência na base:
    //TPB = 15 + paciência de H * aleatório [1...20]
    //cria e insere na LEF o evento SAI (agora + TPB, H, B)
}

void sai(int tempo, struct heroi *heroi, struct base *base)
{
    //retira H do conjunto de heróis presentes em B
    //escolhe uma base destino D aleatória
    //cria e insere na LEF o evento VIAJA (agora, H, D)
    //cria e insere na LEF o evento AVISA (agora, B)
}

void viaja(int tempo, struct heroi *heroi, struct base *base)
{
    //calcula duração da viagem:
    //distância = distância cartesiana entre a base atual de H e a base D 
    //duração = distância / velocidade de H
    //cria e insere na LEF o evento CHEGA (agora + duração, H, D)
}

void morre(int tempo, struct heroi *heroi, struct base *base)
{
    //retira H do conjunto de heróis presentes em B
    //muda o status de H para morto 
    //cria e insere na LEF o evento AVISA (agora, B)
}

//missao

//fim