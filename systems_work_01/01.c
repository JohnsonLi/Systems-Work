#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Multiples of 3 and 5
// 0 - 1000
int multiple35(){
    int i;
    int sum = 0;
    for(i = 0; i < 1000; i++){
        if(i % 3 == 0 || i % 5 == 0){
            sum += i;
        }
    }
    return sum;
}

// Smallest multiple
// 1-20
// Need to divide by 20, 19, 18, 17, 16, 15, 14, 13, 12 (actually not needed because 20 and 18), 11
// I know there's a faster way but -_-
int smallest_multiple(){
    int n = 20;
    while (n % 11 != 0 || n % 13 != 0 || n % 14 != 0 || n % 15 != 0 || n % 16 != 0 || 
           n % 17 != 0 || n % 18 != 0 || n % 19 != 0 || n % 20 != 0){
        n+=20;
    }
    return n;
}

// Sum square difference
// 1 - 100
int sum_square_difference(){
    int i;
    int sum = 0;
    int sum_square = 0;
    for(i = 1; i <= 100; i++){
        sum+= i;
        sum_square += i * i;
    }

    return sum * sum - sum_square;
}

int main(){
    printf("%d\n", multiple35());
    printf("%d\n", smallest_multiple());
    printf("%d\n", sum_square_difference());
    return 0;
}