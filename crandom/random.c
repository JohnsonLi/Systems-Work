#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int generate_num(){
    int file = open("/dev/random", O_RDONLY);
    if(file < 0){
        printf("%s\n", strerror(errno));
        return file;
    }

    int num;
    int read_file = read(file, &num, sizeof(num));
    if(read_file < 0){
        printf("%s\n", strerror(errno));
        return read_file;
    } else {
        return num;
    }

    if(close(file) == 0){
        printf("file closed successfully");
    }
}

int main(){

    // printf("random number: %d\n", generate_num());
    int nums[10];

    int i;
    printf("generating random numbers:\n");
    for(i = 0; i < 10; i++){
        nums[i] = generate_num();
        printf("\trandom %d: %d\n", i, nums[i]);
    }

    printf("\nwriting numbers to file\n");
    int write_file = open("random.txt", O_CREAT | O_WRONLY, 0700);
    if(write_file < 0){
        printf("%s\n", strerror(errno));
        return write_file;
    }
    int writing = write(write_file, nums, sizeof(int) * 10);
    if(writing < 0){
        printf("%s\n", strerror(errno));
        return writing;
    } else {
        printf("successfully wrote to file\n");
    }
    if(close(write_file) == 0){
        printf("write_file closed successfully\n\n");
    } else {
        printf("%s\n", strerror(errno));
        return write_file;
    }

    printf("reading numbers from file\n");
    int file_nums[10];
    int read_file = open("random.txt", O_RDONLY);
    if(read_file < 0){
        printf("%s\n", strerror(errno));
        return read_file;
    }
    int reading = read(read_file, file_nums, sizeof(file_nums));
    if(reading < 0){
        printf("%s\n", strerror(errno));
        return reading;
    } else {
        printf("successfully read from file\n");
    }
    if(close(read_file) == 0){
        printf("read_file closed successfully\n\n");
    } else {
        printf("%s\n", strerror(errno));
        return read_file;
    }

    printf("verification that written values were the same:\n");
    for(i = 0; i < 10; i++){
        printf("\trandom %d: %d\n", i, file_nums[i]);
    }

    return 0;
}