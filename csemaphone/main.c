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
#include "control.h"

#define FILENAME "story.txt"

int ftokHelper() {
    char fileLocation[200];
    char cwd[150];
    strcpy(fileLocation, getcwd(cwd, sizeof(cwd)));
    strcpy(fileLocation, "control.c");
    return ftok(fileLocation, 5);
}

int main(){
	int key = ftokHelper();
	int semid = semget(key, 1, 0644);
    int shmid = shmget(key, 200, 0644);
	int fd = open(FILENAME, O_RDWR | O_APPEND);
	if (fd == -1) {
        printf("Error opening the file: %s\n", strerror(errno));
        return 0;
    }
	printf("Checking if resources are availible...\n");

	struct sembuf ops;
    ops.sem_num = 0;
    ops.sem_op = -1;
    ops.sem_flg = SEM_UNDO;
	semop(semid, &ops, 1);
	printf("Resources availible\n\n");

	char *last_line = shmat(shmid, 0, 0);
	if(strlen(last_line) == 0){
		printf("Nothing in story yet. Add something!\n");
	} else {
		printf("Last line in story:\n");
		printf("%s\n", last_line);
	}

	printf("Add a new line to the story:\n");
	char input[1024];
	fgets(input, 1024, stdin);
	write(fd, input, strlen(input));
	input[strlen(input) - 1] = 0;
	strcpy(last_line, input);
	printf("Line added!\n");

	ops.sem_op = 1;
	semop(semid, &ops, 1);

	close(fd);
	shmdt(last_line);
	
    return 0;
}

