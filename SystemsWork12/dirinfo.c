#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main (int argc, char *argv[]) {
    char dir_path[500];

    if (argc < 2) {
        printf("No command line argument for directory found\n");
        while (1) {
            printf("Type './' for this directory\n");
            printf("Enter a directory name: ");
            fgets(dir_path, sizeof(dir_path), stdin);
            if (!(strlen(dir_path) == 0 || dir_path[0] == '\n')) {
                break;
            }
        }
    } else {
        strcpy(dir_path, argv[1]);
    }

    if (dir_path[strlen(dir_path) - 1] == '\n'){
        dir_path[strlen(dir_path) - 1] = '\0';
    }

    printf("Looking at directory '%s':\n", dir_path);  

    DIR * dir_stream = opendir(dir_path);

    if (!dir_stream) {
        printf("----ERROR----\n");
        printf("%s\n", strerror(errno));
        return -1; 
    }

    struct dirent * cur = readdir(dir_stream);

    int size = 0;
    struct stat * buffer = malloc(sizeof(struct stat));

    while (cur != NULL) {
        char filePath[256];
        strcpy(filePath, "./");
        strcat(filePath, cur->d_name);
        stat(filePath, buffer);
        if(cur -> d_type != 4){
            size += buffer -> st_size;
        }
        printf("%s", cur->d_name);
        if (cur -> d_type == 4) {
            printf(" (Directory)");
        }
        printf("\n");

        cur = readdir(dir_stream);
    }

    printf("Size of files in directory '%s': %d bytes\n", dir_path, size);
    closedir(dir_stream);
    return 0;
}

