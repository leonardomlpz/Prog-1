#include <stdio.h>
int main(){
    int x;
    scanf ("%d", &x);
    switch (x){
        case 1: printf ("numero %d", x);
        case 2: printf ("numero maior que 1\n");
    }

    return 0;
}