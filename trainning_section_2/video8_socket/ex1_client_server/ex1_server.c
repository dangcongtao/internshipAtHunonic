/* server */

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>


int main (int argc, char* argv[])
{
	int listen_socket = -1;
	int connect_socket = -1, opt =1, err = 0;
	struct sockaddr_in server_addr;	
	char send_buffer[1024];
	char *hello ="hello";
	/* addres len to point to server_addr_len, function accept need it in syntax */
	int address_len = 0;


	memset(&server_addr, 0 , sizeof(server_addr));
	memset(send_buffer, 0 , sizeof(send_buffer));

	/* create socket succes */
	listen_socket = socket(AF_INET, SOCK_STREAM, 0);

	/* check setsockopt */
	err = setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR| SO_REUSEPORT, &opt, sizeof(opt));
	if (err < 0) {
		printf ("setsock Err: %d\n", err);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("192.168.0.164");
	server_addr.sin_port = htons(5000);
	
	/* bind sucess */
	err = bind(listen_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (err != 0){
		printf("bind Err: %d", err);
	}
	
	/* create a queue */
	listen(listen_socket,10);
	
	address_len = sizeof(server_addr);
	connect_socket = accept(listen_socket, (struct sockaddr*)&server_addr, (socklen_t*)&address_len);
	if (connect_socket < 0 ){
		printf("accept err: %d\n", connect_socket);
	}
	/* strcpy(send_buffer, "server reply"); */
	err = send(connect_socket, hello, strlen(hello), 0);
	printf ("bytes sent: %d\n", err);
	close(connect_socket);
	
	close(listen_socket);

	return 0;
}
