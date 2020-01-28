#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "header_client.h"
#include "header_server.h"

void init_server(){
  token = 0;
  server_id = 1;

  /* ftok to generate unique key */
  key_server = ftok("server", server_id);

  /* msgget creates a message queue and returns identifier*/
  msgque_id_server = msgget(key_server, 0666 | IPC_CREAT);

  if(msgque_id_server != -1){
    printf("Server initialized!\n");
    sleep(1);
  }
  else{
    printf("Failed to initialize server!\n");
  };
}

void init_client(){
  printf("Please, type client_id you want for this client and press Enter...\n");
  printf("client_id = ");
  scanf("%i",&client_id);

  /* ftok to generate unique key for client */
  key_client = ftok("client", client_id);

  /* msgget creates a message queue and returns identifier */
  msgque_id_client = msgget(key_client, 0666 | IPC_CREAT);

  if(msgque_id_client != -1){
    printf("Client initialized!\n");
    printf("msgque_id_client = %i\n", msgque_id_client);
    printf("msgque_id_server = %i\n", msgque_id_server);
    sleep(1);
  }
  else{
    printf("Failed to initialize client!\n");
  };
}

void send_request(){
  /* here, the client should sent a request to server with the message queue id client */
  printf("Sending request to server...\n");
  sleep(1);
  /* msgsnd to send message */
  message.msgque_id_client = msgque_id_client;
  message.mesg_type = 1;
  message.token = 0;
  if(msgsnd(msgque_id_server, &message, sizeof(message), 0) != -1){
    printf("Request sent to server!\n");
    sleep(1);
  }
  else{
    printf("Failed sending request to server!\n");
    sleep(1);
  };
}

void recv_token(){
  /* msgrcv to receive message */
  printf("Receiving token from server...\n");
  sleep(1);
  if(msgrcv(msgque_id_client, &message, sizeof(message), 1, 0) != 0 && message.msgque_id_client == msgque_id_client){
    printf("Token received!\n");
    sleep(1);
    /* display the message */
    printf("Token = %i received at client with Message Queue ID = %i\n", message.token, message.msgque_id_client);
  }
  else{
    printf("Token not received!\n");
  };
}

void close_client(){
  /* to destroy the message queue */
  if(msgctl(msgque_id_client, IPC_RMID, NULL) != -1){
    printf("Client closed!\n");
  }
  else{
    printf("Failed closing client!\n");
  };
}
