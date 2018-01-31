/*
 * Cycle the value of external variable
*/

#include <stdio.h>

int t = 1;

void cycle(int *var, int min, int max) {
    if (min <= *var && *var < max) {
        ++*var;
        return;
    }
    if (*var == max)
        *var = min;
}

int main(){
    cycle(&t, 1, 3);
    cycle(&t, 1, 3);
    printf("%d", t);
}
