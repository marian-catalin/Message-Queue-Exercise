#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "header_server.h"
#include <string.h>

void init_server(){
  token = 0;
  server_id = 1;

  /* ftok to generate unique key */
  key_server = ftok("server", server_id);

  /* msgget creates a message queue and returns identifier*/
  msgque_id_server = msgget(key_server, 0666 | IPC_CREAT);

  if(msgque_id_server != -1){
    printf("Server initialized!\n");
    printf("msgque_id_server = %i\n", msgque_id_server);
    sleep(1);
  }
  else{
    printf("Failed to initialize server!\n");
  };
}

void run_server(){
    struct mesg_queue message;
    printf("The server is waiting for request...\n");
    int j = msgrcv(msgque_id_server, &message, sizeof(message), 1, 0);
    if(j != 0){
      printf("Request received from client with Message Queue ID = %i\n", message.msgque_id_client);

      token++;
      message.token = token;

    /* msgsnd to send message */
      printf("Sending token to client...\n");
      sleep(1);
      if(msgsnd(message.msgque_id_client, &message, sizeof(message), 0) != -1){
          printf("Token sent!\n");
          sleep(1);
          printf("Token = %i sent to client with Message Queue ID = %i\n", message.token, message.msgque_id_client);
          memset(&message, 0, sizeof(message));
          printf("Restart waiting? If yes, type 0 and press Enter...\n");
          scanf("%i",&i);
      }
      else{
          printf("Failed to send token to client!\n");
          printf("Restart waiting? If yes, type 0 and press Enter...\n");
          scanf("%i",&i);
      };
    }
    else{
      printf("Request not received!\n");
      printf("Restart waiting? If yes, type 0 and press Enter...\n");
      scanf("%i",&i);
    };
  }
