#include "pipe_networking.h"

static void sighandler(int signo){
  if(signo == SIGINT){
    printf("\n");
    printf("Removing files...\n");
    remove("plumber");
    char pid[HANDSHAKE_BUFFER_SIZE];
    sprintf(pid, "%d", getpid());
    remove(pid);
    printf("Now exiting...\n");
    exit(0);
  }
}

int main() {

  int to_client;
  int from_client;

  signal(SIGINT, sighandler);

  while(1){
    printf("Waiting for client to connect\n");
    mkfifo("plumber", O_CREAT | 0644);
    char data[BUFFER_SIZE];
    from_client = open("plumber", O_RDONLY);
    
    if(!fork()){
      to_client = server_handshake(from_client);
      while(read(from_client, data, sizeof(data))){
        printf("Recieved '%s' from client\n", data);
        data[strlen(data)] = 0;

        int i;
        for(i = 0; i < strlen(data); i++){
          data[i] += 5;
        }

        write(to_client, data, BUFFER_SIZE);
        printf("Replying '%s' to client\n", data);
      }
      exit(0);
    } else {
      close(from_client);
      remove("plumber");
    }
    
  }
}
