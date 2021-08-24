/* CLIENT SIDE */


#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h> 
#include <string.h> /* for memset */
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#define PORT = 5000
#define IP_CLIENT "192.168.0.164"

int main (int argc, char *argv[])

{
	
	/* INIT SOCKET */
	int my_socket = socket(AF_INET, SOCK_DGRAM, 0);
	int err = 0, addres_len, bytes_sent = 0;
	struct sockaddr_in server_adress;
	socklen_t *serv_addres_len;

	/* declare return value of server send for client.
	 * 1MB */
	char receive_buffer[1024];

	/* memset */
	memset(&server_adress, 0 , sizeof(server_adress));
	memset(receive_buffer, 0 , sizeof(receive_buffer));	
	
	/* set values for server address. */
	server_adress.sin_family = AF_INET;

	/* set ip address */
	/* server_adress.sin_addr.s_addr = inet_addr("192.168.0.164"); */
	err = inet_pton(AF_INET,IP_CLIENT, &server_adress.sin_addr.s_addr);
	if (err < 0 ) {
		printf ("Set IP err: %d\n", err);
	}
	server_adress.sin_port = htons(5000);
	
    addres_len = sizeof(server_adress);
	
    /* send to server, turn on connect mode. */
    bytes_sent = sendto(my_socket, "hello", sizeof("hello"), 0, (struct sockaddr*)&server_adress, (socklen_t)addres_len );
	printf ("bytes sent: %d\n", bytes_sent);
	
	serv_addres_len = &addres_len;

	err = -1;
	while (err < 0){
		printf ("server IP: %s\n", inet_ntoa(server_adress.sin_addr));
		printf ("my socket: %d\n",my_socket);
		printf ("addres len: %d\nbuffer: %s\n", addres_len, receive_buffer);
		
		err = read (my_socket, receive_buffer, sizeof(receive_buffer));
		
		#pragma region function read socket
		/* err = recv(my_socket,&receive_buffer, sizeof(receive_buffer), 0); */
		/* err = recvfrom(my_socket, &receive_buffer, sizeof(receive_buffer), 0 , NULL, NULL); */
		#pragma endregion

		printf ("ERR: %d\nbuffer: %s\n", err, receive_buffer);
	}
	
	
	return 0;
}