#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

int token = 0;

struct mesg_queue {
    long mesg_type;
    int msgque_id_client;
    int token;
} message;

int main(){
  printf("Starting server...\n");

  int i;

  key_t key_server;
  int msgque_id_server;
  int server_id = 1;

  /* ftok to generate unique key */
  key_server = ftok("server", server_id);

  /* msgget creates a message queue
  and returns identifier*/
  msgque_id_server = msgget(key_server, 0666 | IPC_CREAT);


  label: printf("Start waiting? If yes, type 0 and press Enter...\n");
  scanf("%i",&i);
  if(i == 0){
    printf("The server is waiting for request...\n");
    printf("msgque_id_server = %i\n", msgque_id_server);

  /*aici o sa se receptioneze mesajul clientului (mesaj de tip structura ce contine msgque_id_client, msgtype si token)*/
  /* msgrcv to receive message */
    if(msgrcv(msgque_id_server, &message, sizeof(message), 1, 0) != 0){
      printf("Request received from a client with the Message Queue ID = %i\n", message.msgque_id_client);

      token++;
      message.token = token;

    /* msgsnd to send message */
      printf("Sending token to the client...\n");
      sleep(2);
      msgsnd(message.msgque_id_client, &message, sizeof(message), 0);

    /* display the message */
      printf("Message Sent!\n");
      sleep(1);
      printf("Data sent is: Message Queue Client ID = %i , Token = %i\n", message.msgque_id_client, message.token);
      goto label;
    }
    else{
      printf("Request not received!\n");
      goto label;
    };
  }
  else{
    printf("Server closed!\n");
  };

  return 0;
}
