.PHONY: build server, run_server, run_client, remove


build: server client

run_server: server client
	./server
run_client: client
	./client
server: ex1_server.c
	gcc -o server ex1_server.c

client: ex1_client.c
	gcc -o client ex1_client.c


remove:
	rm client server
