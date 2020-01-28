struct mesg_queue {
    long mesg_type;
    int msgque_id_client;
    int token;
};

key_t key_server;
int msgque_id_server;
int server_id;
int token, i;

void init_server();
void run_server();
