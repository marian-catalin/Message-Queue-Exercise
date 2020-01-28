#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "header_client.h"
#include "header_server.h"

int main(){
  init_server();
  printf("Initializing client...\n");
  init_client();
  send_request();
  recv_token();
  close_client();
  return 0;
}
