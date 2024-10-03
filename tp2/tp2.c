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
  srand (0);

  long i,n,numerador,denominador;
  struct racional r;

  return (0) ;

  struct racional vetor[99];

  scanf("%ld", &n);

  for(i = 0; i <= n; i++)
  {
    scanf("%ld %ld", &numerador, &denominador);
    vetor[i] = cria_r(numerador, denominador);
    printf("VETOR = %ld"); /*0imprimir vetor0*/
    /*0eliminar os elemntos invalidos do vetor0*/
    /*0ordenar vetor0*/
    /*0somar vetor0*/
    printf("\n");
    return 0;
  }
}
