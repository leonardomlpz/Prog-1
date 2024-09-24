/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

long aleat (long min, long max)
{
  return rand() % (max - min + 1) + min;
}

/* programa principal */
int main ()
{
  struct racional r;
  srand (0); /* use assim, com zero */

  int i,n,max;

  scanf ("%d", &n);
  scanf ("%d", &max);

  for (i = 1; i <= n; i++)
  {
    printf ("%d: ", i);
    struct racional r1 = sorteia_r (-max, max);
    struct racional r2 = sorteia_r (-max, max);
    imprime_r (r1)
  }
  

  return (0) ;
}
