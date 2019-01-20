#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// slowest possible sieve
int sieve(int target){

    int size = (int)(target * log(target) * 1.5);
    char *arr = malloc(size);
    int count = 0;

    int i;
    for(i = 2; i < size; i++){
        
        // if index is not composite count ++
        if(arr[i] != 'c'){
            count++;
            
            int j;
            // mark all multiples of i as composite 
            for(j = i; j < size; j+=i){
                arr[j] = 'c';
            }
        }

        // if on target'th, prime return it
        if(count == target){
            return i;
        } 
    }

    return -1;
}