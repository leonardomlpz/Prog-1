/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */

void quick_sort(struct racional vetor[], int n) {
    int menor = 0;
    int maior = n - 1;

    while (menor < maior)
    {
        // Escolhe o pivô
        struct racional pivo = vetor[maior];
        int i = menor - 1;

        // Particiona o vetor
        for (int j = menor; j < maior; j++)
        {
            if (compara_r(vetor[j], pivo) < 0)
            {
                i++;
                struct racional temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
            }
        }
        struct racional temp = vetor[i + 1];
        vetor[i + 1] = vetor[maior];
        vetor[maior] = temp;
        int novoPivo = i + 1;

        // Ajusta os limites
        if (novoPivo - menor < maior - novoPivo)
        {
            // Ordena a parte menor primeiro
            quick_sort(vetor + menor, novoPivo - menor);
            menor = novoPivo + 1; // Ajusta menor para a próxima iteração
        }
        else
        {
            // Ordena a parte maior primeiro
            quick_sort(vetor + novoPivo + 1, maior - novoPivo);
            maior = novoPivo - 1; // Ajusta maior para a próxima iteração
        }
    }
}

/* programa principal */
int main ()
{
  long i,n,tam,numerador,denominador;
  struct racional vetor[99];

  scanf("%ld", &n);
  tam = n;
  for(i = 0; i < n; i++)
  {
    scanf("%ld %ld", &numerador, &denominador);
    vetor[i] = cria_r(numerador, denominador);
  }

  printf ("VETOR =");

  for (i = 0; i < n; i++)
  {
    printf (" ");
    imprime_r(vetor[i]);
  }

  printf ("\n");

  /*0eliminar os elemntos invalidos do vetor0*/
  for (i = 0; i < n; i++)
  {
    if (valido_r(vetor[i]) == 0)
    {
      for (int j = n - 1; j > 1 ; j--)
      {
        if(valido_r(vetor[j]) == 0)
          tam--;
        else {
        vetor[i] = vetor[j];
        n = j;
        break;
        }
      }
    }
  }
  n++;
  printf ("VETOR =");

  for (i = 0; i < n; i++)
  {
    printf (" ");
    imprime_r(vetor[i]);
  }

  printf ("\n");

  /*0ordenar vetor0*/
  quick_sort(vetor,n);

  printf ("VETOR =");

  for (i = 0; i < n; i++)
  {
    printf (" ");
    imprime_r(vetor[i]);
  }

  printf ("\n");

  /*0somar vetor0*/
  struct racional soma={0,1};
  for (i = 0; i < n; i++)
  {
    struct racional temp;
    soma_r(vetor[i],soma,&temp);
    soma.num = temp.num;
    soma.den = temp.den;
  }
  printf("SOMA =");
  printf(" ");
  imprime_r(soma);

  printf("\n");
  return 0;
}
