/* SERVER SIDE */


#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <error.h>

#define PORT 5000
#define IP_SERV "192.168.0.164"

int main (int argc, char *argv[]) {

    struct sockaddr_in serv_addr, client_addr;
    int UDP_sockfd = 0, err = 0, bytes_sent = 0, bytes_read = 0, client_addr_len;
    char hello_fromserv[1024] = "hello this is message form server UDP Broadcast";
    char client_mssg[1024], *client_ip_string;
    int broadcast_permission = 1;
    socklen_t serv_addr_len;



    
    /* socket with UDP transport protocol */
    UDP_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   
   /* set option SO_BROADCAST for socket. */
    setsockopt(UDP_sockfd, SOL_SOCKET, SO_BROADCAST, (void*)&broadcast_permission, sizeof(broadcast_permission));

    /* set address to send to this addr */
    client_addr.sin_family = AF_INET;
    inet_pton(AF_INET,"192.168.0.255", &client_addr.sin_addr.s_addr);
    client_addr.sin_port = htons(PORT);

    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.0.164", &serv_addr.sin_addr.s_addr);
    serv_addr.sin_port = htons(PORT);

    client_addr_len = sizeof(client_addr);
    printf ("serv Addr len: %d\n", client_addr_len);
    
    /* to receive a package U must bind to assign a port. */
    err = bind (UDP_sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (err < 0) {
        printf ("bind err: %d\n", err);
    }




    
    bytes_read  = 1;
    client_addr_len = sizeof (client_addr);
    
    printf ("client ip = %s   PORT: %d\n" ,inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    /* sent to client. */
    while (1){

        bytes_sent = sendto(UDP_sockfd, hello_fromserv, strlen(hello_fromserv), 0,(struct sockaddr *)&client_addr, (socklen_t)client_addr_len);

        printf ("Bytes sent: %d\n", bytes_sent);
    }
      

    return 0;
}
