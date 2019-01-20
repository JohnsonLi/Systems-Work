#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    char *file_name = "TEXT.txt";
    char chars[100];

    int file = open(file_name, O_CREAT | O_WRONLY);

    printf("opening a file called 'TEXT.txt' or create it if it doesn't exist\n");
    printf("file object: %d\n", file);

    int x;
    printf("writing 'HEYO\\n' to TEXT.txt\n");
    x = write(file, "HEYO\n", strlen("HEYO\n"));
    printf("write object: %d\n", x);

    if(close(file) == 0){
        printf("write file closed\n");
    }


    file = open(file_name, O_RDONLY);

    int y;
    printf("reading from TEXT.txt\n");
    y = read(file, chars, 5);
    printf("read object: %d\n", y);
    printf("printing things from read object:\n");
    printf("%s", chars);

    if(close(file) == 0){
        printf("read file closed\n");
    }

    return 0;
}
