#include <stdio.h>


int main(){
    int a,b;
    scanf ("%d %d", &a, &b);
    while ((a != 0) && (b != 0))
  {
    if (a > b){
      a = (a % b);
    }
    else
    {
      b = (b % a);
    }
    if (a == 0){
      printf ("%d\n", b);
    }
    else if (b == 0){
      printf ("%d\n", a);
    }
  }
  return 0;
}