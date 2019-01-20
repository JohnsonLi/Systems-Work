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
  printf("WKP created, waiting for connection...\n");
  int receive = open("plumber", O_RDONLY);
  remove("plumber");

  char client_res[BUFFER_SIZE];
  read(receive, client_res, BUFFER_SIZE);
  printf("Client connected... pid recieved: %s\n", client_res);

  printf("Sending acknowledgement\n");
  int client_pipe = open(client_res, O_WRONLY);
  write(client_pipe, ACK, sizeof(ACK));



  return client_pipe;
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

  char pid[BUFFER_SIZE];
  sprintf(pid, "%d", getpid());
  mkfifo(pid, O_CREAT | 0644);
  printf("Pipe created, connecting to server...\n");
  
  int server = open("plumber", O_WRONLY);
  write(server, pid, sizeof(pid)); 
  printf("Connected to server... pid sent: %s\n", pid);

  char ack[BUFFER_SIZE];
  int server_ack = open(pid, O_RDONLY);
  read(server_ack, ack, sizeof(ack));
  printf("Acknowledgement recieved: %s\n", ack);

  return server;
}
