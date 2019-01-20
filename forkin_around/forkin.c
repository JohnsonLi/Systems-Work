#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <time.h>

int main(){

    srand(time(NULL));
    int rand_nums[2] = {rand(), rand()};

    printf("ABOUT TO FORK\n");

    int child1 = fork();
    if(!child1){
        printf("child1 pid: %d\n", getpid());

        int time_to_sleep = rand_nums[0] % (20 - 5 + 1) + 5;
        sleep(time_to_sleep);

        printf("child1 (%d) finished\n", getpid());
        return time_to_sleep;
    }

    int child2 = fork();
    if(!child2){
        printf("child2 pid: %d\n", getpid());

        int time_to_sleep = rand_nums[1] % (20 - 5 + 1) + 5;
        sleep(time_to_sleep);

        printf("child2 (%d) finished\n", getpid());
        return time_to_sleep;
    }

    int p, status;
    p = wait(&status);

    printf("\n");
    if(WIFEXITED(status)){
        printf("A child is finished\n");
        printf("Child %d finished in %d seconds.\n", p, WEXITSTATUS(status));
        printf("Parent is done, another child may still be running\n");
    } else {
        printf("something went wrong D: \n");
        printf("%s\n", strerror(errno));
    }


    return 0;
}
