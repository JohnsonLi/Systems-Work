#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

int main(){

    key_t key;
    int shmid;
    char *data;

    key = ftok("hi", 'R');
    shmid = shmget(key, 1024, 0644 | IPC_CREAT);

    data = shmat(shmid, 0 ,0);

    if(!data[0]){
        printf("Segment created, nothing in it yet\n");
    } else {
        printf("Content in segment: %s\n", data);
    }

    printf("Do you want to change contents of segment?\n");
    char input[100];
    fgets(input, sizeof(input), stdin);
    if(strstr(input, "yes")){
        printf("Enter new content:\n");
        fgets(input, sizeof(input), stdin);
        strcpy(data, input);
        printf("content now: %s\n", data);
    }

    printf("Do you want to delete the segment?\n");
    fgets(input, sizeof(input), stdin);
    if(strstr(input, "yes")){
        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL);
    }


    return 0;
}