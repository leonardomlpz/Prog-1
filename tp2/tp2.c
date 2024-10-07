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

/* programa principal */
int main ()
{
  long i,n,numerador,denominador;
  struct racional *r;
  struct racional vetor[99];

  scanf("%ld", &n);

  for(i = 0; i < n; i++)
  {
    scanf("%ld %ld", &numerador, &denominador);
    vetor[i] = cria_r(numerador, denominador);
  }

  printf ("VEOTR =");

  for (i = 0; i < n; i++)
  {
    printf (" ");
    imprime_r(vetor[i]);
  }

  printf ("\n");

  /*0eliminar os elemntos invalidos do vetor0*/
  for (i = 0; i < n; i++)
  {
    if (vetor[i].den == 0)
    {
      for (int j = i; j < n - 1; j++)
        vetor[j] = vetor[n];
        n
    }
  }

  printf ("VEOTR =");

  for (i = 0; i < n; i++)
  {
    printf (" ");
    imprime_r(vetor[i]);
  }

  printf ("\n");

  /*0ordenar vetor0*/
  for (int i = 0; i < n -1; i++)
  {
    for (int j = 0; j < n -i -1; j++)
    {
      if (compara_r(vetor[j],vetor[j + 1]) > 0)
      {
        struct racional temp = vetor[j];
        vetor[j] = vetor[j + 1];
        vetor[j + 1] = temp;
      }
    }
  }

  printf ("VEOTR =");

  for (i = 0; i < n; i++)
  {
    printf (" ");
    imprime_r(vetor[i]);
  }

  printf ("\n");

  /*0somar vetor0*/
  struct racional soma={0,0};
  for (i = 0; i < n - 5; i++)
  {
    soma_r(vetor[i],vetor[i + 1],&r);
    soma.num = soma.num + r->num;
  }
  printf ("SOMA = %ld/%ld", soma.num,soma.den);
  for (i = 0; i < n; i++)
  {
    printf (" ");
    imprime_r(vetor[i]);
  }
  printf("\n");
  return 0;
}
