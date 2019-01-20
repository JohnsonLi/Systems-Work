#include "pipe_networking.h"

static void sighandler(int signo){
  if(signo == SIGINT){
    printf("\n");
    printf("Removing files...\n");
    char pid[HANDSHAKE_BUFFER_SIZE];
    sprintf(pid, "%d", getpid());
    remove(pid);
    printf("now exiting...\n");
    exit(0);
  }
}

int main() {

  int to_server;
  int from_server;
  
  from_server = client_handshake( &to_server );
  signal(SIGINT, sighandler);

  char data[BUFFER_SIZE];
  while(1){
    printf("Enter something: \n");
    fgets(data, sizeof(data), stdin);
    data[strlen(data) - 1] = 0;

    printf("Sending '%s' to server\n", data);
    write(to_server, data, sizeof(data));


    read(from_server, data, sizeof(data));
    printf("Recieved '%s' from server\n", data);

  }
    
}
