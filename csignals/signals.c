#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

static void sighandler(int signo){

    if(signo == SIGINT){
        int fd = open("exit.txt", O_CREAT | O_WRONLY, 0644);
        if(fd < 0){
            printf("%s\n", strerror(errno));
            return;
        }
        write(fd, "Program exited due to SIGINT.\n", strlen("Program exited due to SIGINT.\n"));
        close(fd);

        printf("\ncheck created file...\n");
        exit(0);
    }

    if(signo == SIGUSR1){
        printf("parent pid: %d\n", getppid());
    }

}

int main() {
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);

    while(1){
        printf("current pid: %d\n", getpid());
        sleep(1);
    }

    return 0;
}
