#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    
    int ary[10];
    srand(time(NULL));

    int i;
    for(int i = 0; i < sizeof(ary) / 4; i++){
        ary[i] = rand();
    }

    ary[9] = 0;
    printf("first array\n");
    for(int i = 0; i < sizeof(ary) / 4; i++){
        printf("element %d : %d\n", i, ary[i]);
    }

    printf("second array\n");
    int ary_other[10];
    for(int i = 0; i < sizeof(ary_other) / 4; i++){
        *(ary_other + i) = *(ary + 9 - i);
        printf("element %d : %d\n", i, ary_other[i]);
    }



    return 0;
}
