#include <stdio.h>
int main(){
    int x,y;

    printf ("Digite os numeros a serem mukltiplicados: ");
    scanf ("%d %d", &x, &y);
    printf ("%d multiplicado por %d resulta em %d\n", y, x, x *y);

    return 0;
}