#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "header_server.h"

int main(){
  printf("Initializing server...\n");
  init_server();
  printf("Starting server...\n");
  printf("Start waiting? If yes, type 0 and press Enter...\n");
  scanf("%i",&i);
  while(i == 0){
    run_server();
  }
  printf("Server closed!\n");
  return 0;
}
