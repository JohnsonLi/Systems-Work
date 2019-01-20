#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

char *human_readable(char *buffer, long size){

    // 1024 bytes in a kilobyte
    if(size < 1024){
        sprintf(buffer, "%ld bytes", size);
        return buffer;
    }
    // 1024 * kilobytes  = megabytes
    if(size < 1048576){
        sprintf(buffer, "%f kilobytes", size / 1024.0);
        return buffer;
    }
    // 1024 * megabytes = gigabytes
    if(size < 1073741824){
        sprintf(buffer, "%f gigabytes", size / 1048576.0);
        return buffer;
    }

}

int main(){
    char file_size[50];

    char *FILE_NAME = "makefile";
    printf("File name: %s\n", FILE_NAME);

    struct stat *info = malloc(sizeof(struct stat));

    stat(FILE_NAME, info);
    printf("file size: %ld\n", info->st_size);
    printf("permissions of file: %d\n", info->st_mode);
    printf("time of last access: %s\n", ctime(&(info->st_atime)));

    printf("file size(human readable): %s\n", human_readable(file_size, info->st_size));

    char permissions[10] = "rwxrwxrwx\0";

    int i;
    for(i = 0; i < 9; i++){
        // check each from last 9 bytes
        if(!((info->st_mode) & (1 << (8 - i)))){
            permissions[i] = '-';
        }
    }
    printf("permissions like in ls -l: %s\n", permissions);

    return 0;
}
