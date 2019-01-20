#include <stdio.h>
#include <stdlib.h>

unsigned int big = 2100000001;

char *pointy = &big;

int main(){
    printf("int in hex: %x\n", big);  // int in hex

    int i;
    for(i = 0; i < 4; i++){
        printf("byte of int: %hhx\n", *pointy);
        pointy++;
    }

    pointy = &big;
    for(i = 0; i < 4; i++){
        *pointy+= 1;
        printf("byte of int increased by 1: %x %d\n", big, big);
 
    }

    pointy = &big;
    for(i = 0; i < 4; i++){
        *pointy+= 16;
        printf("byte of int increased by 16: %x %d\n", big, big);
 
    }

    return 0;
}