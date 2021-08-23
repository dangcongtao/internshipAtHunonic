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

int main (int argc, char *argv[])
{
	/* INIT SOCKET */
	int my_socket = socket(AF_INET, SOCK_STREAM, 0);
	int err = 0;
	/* declare server add */
	struct sockaddr_in my_server_adress;

	/* declare return value of server send for client.
	 * 1MB */
	char receive_buffer[1024];


	memset(&my_server_adress, 0 , sizeof(my_server_adress));
	memset(receive_buffer, 0 , sizeof(receive_buffer));	
	
	/* set values for server address. */
	my_server_adress.sin_family = AF_INET;

	/* set ip address */
	/* my_server_adress.sin_addr.s_addr = inet_addr("192.168.0.164"); */
	err = inet_pton(AF_INET,"192.168.0.164", &my_server_adress.sin_addr.s_addr);
	if (err < 0 ) {
		printf ("Set IP err: %d\n", err);
	}

	/* set port */
	my_server_adress.sin_port = htons(5000);

	err = connect(my_socket, (struct sockaddr *)&my_server_adress, sizeof(my_server_adress) );
	if (err == 0)
	{
		/* connect success */
		printf ("\nconnect sucessfully!!\n");
		int len = 0;
		
		while (len == 0)
		len = read(my_socket, &receive_buffer, 1024);

		printf ("received: %s\n", receive_buffer);

		close(my_socket);
	}else 
	{
		printf("\nconnect err: %d\n", err);
		close(my_socket);
	}

	
	return 0;
}
