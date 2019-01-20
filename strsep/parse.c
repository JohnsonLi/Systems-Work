#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char ** parse_args( char * line ){

    char **args = malloc(15 * sizeof(char *));

    int counter = 0;
    while(line){
        args[counter] = strsep(&line, " ");
        counter++;
    }

    return args;
}

int main(){

    char args[100] = "ls -a -l";
    char **args = parse_args("ls -l");
    
    execvp(args[0], args);

}