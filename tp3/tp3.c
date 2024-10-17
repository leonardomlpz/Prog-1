/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>

/* coloque aqui as funções auxiliares que precisar neste arquivo */

void le_vet(struct racional **vetor, long tam){
  long i,numerador,denominador;
  for(i = 0; i < tam; i++)
  {
    scanf("%ld %ld", &numerador, &denominador);
    vetor[i] = cria_r(numerador, denominador);
  }
  return;
}

void imprime_vet(struct racional *vetor[], long tam)
{
  for (int i = 0; i < tam; i++)
  {
    printf (" ");
    imprime_r(vetor[i]);
  }
}

void quick_sort(struct racional *vetor[], int n) {
    if (n <= 1) {
        return; /* Se o vetor tiver tamanho 0 ou 1 já está ordenado */
    }

    int menor = 0;
    int maior = n - 1;

    /* Escolhe o pivô como o último elemento */
    struct racional *pivo = vetor[maior];
    int i = menor - 1;

    /* Particionamento */
    for (int j = menor; j < maior; j++) {
        if (compara_r(vetor[j], pivo) < 0) {
            i++;
            /* Troca vetor[i] e vetor[j] */
            struct racional *temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
        }
    }

    /* Coloca o pivô na posição correta */
    struct racional *temp = vetor[i + 1];
    vetor[i + 1] = vetor[maior];
    vetor[maior] = temp;
    int novoPivo = i + 1;

    /* Recursividade*/ 
    quick_sort(vetor, novoPivo); /* Ordena a parte esquerda */
    quick_sort(vetor + novoPivo + 1, n - novoPivo - 1); /* Ordena a parte direita */
}

void soma_vet(struct racional *vetor[], long tam)
{
  struct racional *soma = malloc(sizeof(struct racional *));
  soma->num = 0;
  soma.den = 1;
  struct racional temp;
  for (int i = 0; i < tam; i++)
  {
    soma_r(vetor[i],&soma,&temp);
    soma.num = temp.num;
    soma.den = temp.den;
  }
  imprime_r(soma);
}

/* programa principal */
int main ()
{
  int n;
  scanf ("%d", n);

  struct racional **vetor = malloc(n*sizeof(struct racional *));

  le_vet(vetor,n);
  printf ("VETOR = ");
  imprime_vet(vetor,n);

  /*eliminar nulos*/
  printf ("VETOR = ");
  imprime_vet(vetor,n);

  printf ("VETOR = ");
  quick_sort(vetor,n);

  struct racional *soma = malloc(sizeof(struct racional *));
  soma->num = 0;
  soma.den = 1;


  return (0) ;
}

