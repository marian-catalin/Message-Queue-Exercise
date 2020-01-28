make_main_server: main_server.c API_server.c
		gcc -g main_server.c API_server.c -o main_server

make_main_client: main_client.c API_client.c
		gcc -g main_client.c API_client.c -o main_client
