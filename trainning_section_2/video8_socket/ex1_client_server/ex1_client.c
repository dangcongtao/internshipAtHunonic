/* client */

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h> 
#include <string.h> /* for memset */
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define HS_TCP_PORT	49999

int main (int argc, char *argv[])
{
	/* INIT SOCKET */
	int my_socket = socket(AF_INET, SOCK_STREAM, 0);
	int err = 0;
	/* declare server add */
	struct sockaddr_in my_server_adress;

	/* declare return value of server send for client.
	 * 1MB */
	char receive_buffer[1024], *hello = "hello from client TCP";


	memset(&my_server_adress, 0 , sizeof(my_server_adress));
	memset(receive_buffer, 0 , sizeof(receive_buffer));	
	
	/* set values for server address. */
	my_server_adress.sin_family = AF_INET;
	
	/* set port */
	my_server_adress.sin_port = htons(HS_TCP_PORT);

	/* set ip address */
	/* my_server_adress.sin_addr.s_addr = inet_addr("192.168.0.164"); */
	my_server_adress.sin_addr.s_addr = INADDR_ANY;

	
	if (err < 0 ) {
		printf ("Set IP err: %d\n", err);
	}
	printf ("code here\n");

	err = connect(my_socket, (struct sockaddr *)&my_server_adress, sizeof(my_server_adress) );
	if (err == 0)
	{
		/* connect success */
		printf ("\nconnect sucessfully!!\n");
		int len = 0;

		err = send(my_socket, hello, strlen(hello), 0);
		printf ("bytes sent: %d\n", err);
		
		/* while (len == 0)
		len = read(my_socket, &receive_buffer, 1024); */

		printf ("received: %s\n", receive_buffer);

		close(my_socket);
	}else 
	{
		printf("\nconnect err: %d\n", err);
		close(my_socket);
	}

	
	return 0;
}
