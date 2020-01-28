#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct mesg_queue {
    long mesg_type;
    int msgque_id_client;
    int token;
} message;

int main(){
    key_t key_server;
    int msgque_id_server;
    int server_id = 1;

    /* ftok to generate unique key for server */
    key_server = ftok("server", server_id);

    /* msgget creates a message queue
     and returns identifier */
    msgque_id_server = msgget(key_server, 0666 | IPC_CREAT);

    key_t key_client;
    int msgque_id_client;
    int client_id;

    printf("Please, type client_id you want for this client and press Enter...\n");
    printf("client_id = ");
    scanf("%i",&client_id);

    /* ftok to generate unique key for client */
    key_client = ftok("client", client_id);

    /* msgget creates a message queue
     and returns identifier */
    msgque_id_client = msgget(key_client, 0666 | IPC_CREAT);


    printf("msgque_id_client = %i\n", msgque_id_client);
    printf("msgque_id_server = %i\n", msgque_id_server);

    /* here, the client should sent a request to server with the message queue id client */
    printf("Sending request to server...\n");

    /* msgsnd to send message */
    message.msgque_id_client = msgque_id_client;
    message.mesg_type = 1;
    message.token = 0;
    msgsnd(msgque_id_server, &message, sizeof(message), 0);
    sleep(2);

    printf("Request sent to server!\n");

    /* msgrcv to receive message */
    printf("Receiving data from server...\n");
    sleep(2);
    msgrcv(msgque_id_client, &message, sizeof(message), 1, 0);

    if(message.msgque_id_client == msgque_id_client){
      printf("Message received!\n");
      sleep(1);
      /* display the message */
      printf("Data Received is: Message Queue Client ID = %i , Token = %i\n", message.msgque_id_client, message.token);
    }
    else{
      printf("Message not received!\n");
    };

    /* to destroy the message queue */
    msgctl(msgque_id_client, IPC_RMID, NULL);
    printf("Client closed!\n");

    return 0;
}
