.PHONY: server, run_server, run_client

run_server: server client
	./server
run_client: client
	./client
server: ex1_server.c
	gcc -o server ex1_server.c

client: ex1_client.c
	gcc -o client ex1_client.c


clean:
	rm client server
