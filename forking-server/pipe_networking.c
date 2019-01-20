#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  
  mkfifo("plumber", O_CREAT | 0644);

  printf("[Server] WKP created. Waiting for connection...\n");
  int from_client = open("plumber", O_RDONLY);
  printf("[Server] Client connected, forking...\n");

  char client_res[HANDSHAKE_BUFFER_SIZE];

  int a = fork();
  if(a){
    printf("[Subserver %d] Client connected... pid recieved: %s\n", getpid(),client_res);
    read(from_client, client_res, HANDSHAKE_BUFFER_SIZE);
    printf("[Subserver %d] Sending acknowledgement\n", getpid());
    printf("[Subserver %d] Waiting for client data...\n", getpid());
    *to_client = open(client_res, O_WRONLY);
    write(*to_client, ACK, sizeof(ACK));
    remove(client_res);


    return from_client;
  } else {
    close(from_client);
    remove("plumber");
    return 0;
  }
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  printf("Creating pipe...\n");

  char pid[HANDSHAKE_BUFFER_SIZE];
  sprintf(pid, "%d", getpid());
  mkfifo(pid, O_CREAT | 0644);
  printf("[Client %d] Pipe created, connecting to server...\n", getpid());
  
  int server = open("plumber", O_WRONLY);
  *to_server = server;
  write(server, pid, sizeof(pid)); 
  remove("plumber");
  printf("[Client %d] Connected to server... pid sent: %s\n", getpid(), pid);

  char ack[HANDSHAKE_BUFFER_SIZE];
  int server_ack = open(pid, O_RDONLY);
  read(server_ack, ack, sizeof(ack));
  printf("[Client %d] Acknowledgement recieved: %s\n", getpid(), ack);
  remove("plumber");

  return server_ack;
}
