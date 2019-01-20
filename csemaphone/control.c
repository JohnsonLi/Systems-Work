#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define FILENAME "story.txt"

union semun {
	int val; 
	struct semid_ds *buf;   
	unsigned short  *array; 
	struct seminfo  *__buf;
};

int ftokHelper() {
    char fileLocation[200];
    char cwd[150];
    strcpy(fileLocation, getcwd(cwd, sizeof(cwd)));
    strcpy(fileLocation, "control.c");
    return ftok(fileLocation, 5);
}

void createFlag () {
    int fd = open("story.txt", O_TRUNC | O_CREAT, 0664);
    if (fd == -1) {
        printf("Error opening the file: %s\n", strerror(errno));
        return;
    }

    int memKey = ftokHelper();
    int shmid = shmget(memKey, 256, 0644 | IPC_CREAT);
    int semid = semget(memKey, 1, IPC_CREAT | IPC_EXCL | 0664);
    printf("Shared Memory ID: %d\nSemaphore ID: %d (-1 means already exists)\n", shmid, semid);
    union semun data;
    data.val = 1;
    semctl(semid, 0, SETVAL, data);
    close(fd);
}

void viewFlag () {
    int fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        printf("Error opening file: %s\n", strerror(errno));
        return;
    }

    char *story = malloc(8092);
    read(fd, story, 8092);
    printf("%s\n", story);
    free(story);
    close(fd);
}

void removeFlag () {
    printf("Removing sempahone...\n");
    int key = ftokHelper();
    int semid = semget(key, 1, 0644);
    int shmid = shmget(key, 200, 0644);

    while(semctl(semid, 0, GETVAL) == 0) {
        printf("waiting for file\n");
        sleep(1);
    }

    struct sembuf ops;
    ops.sem_num = 0;
    ops.sem_op = -1;
    ops.sem_flg = SEM_UNDO;
    semop(semid, &ops, 1);

    semctl(semid, 0, IPC_RMID);
    shmctl(shmid, IPC_RMID, NULL);

    printf("File contents:\n");
    viewFlag();
    if(remove(FILENAME) == -1){
        printf("Error removing file: %s\n", strerror(errno));
        return;
    }

    ops.sem_op = 1;
    semop(semid, &ops, 1);

    printf("Semaphore removed\n");
}

int main(int argc, char const *argv[]){
    
    if(argc > 1){
        if(!strcmp(argv[1], "-c")) {
            createFlag();
            return 0;
        }

        if(!strcmp(argv[1], "-r")){
            removeFlag();
            return 0;      
        }

        if(!strcmp(argv[1], "-v")){
            viewFlag();
            return 0;
        }
        printf("Please enter a valid command (-c, -r, -v)\n");
    } else {
        printf("Please enter a valid command (-c, -r, -v)\n");
    }

    return 0;
}

