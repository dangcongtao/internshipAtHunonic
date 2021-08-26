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

#define PORT 9000
const char* cmd_udp = "{\"gateway\":1, \"brand\":\"HUNONIC\"}";
char messg_to_broadcast[1024] = "hello this is message form server UDP Broadcast";


int main (int argc, char *argv[]) {

    struct sockaddr_in broadcast_addr;
    int UDP_sockfd = 0, err = 0, bytes_sent = 0, bytes_read = 0, broadcast_addr_len;
    char client_mssg[1024];
    int broadcast_permission = 1;
    socklen_t serv_addr_len;

    /* socket with UDP transport protocol */
    UDP_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   /* set option SO_BROADCAST for socket. */
    setsockopt(UDP_sockfd, SOL_SOCKET, SO_BROADCAST, (void*)&broadcast_permission, sizeof(broadcast_permission));

    /* set address to send to this addr */
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_addr.s_addr = INADDR_BROADCAST;
    broadcast_addr.sin_port = htons(PORT);
    broadcast_addr_len = sizeof(broadcast_addr);

    bytes_read  = 1;
    broadcast_addr_len = sizeof (broadcast_addr);
    
    /* print infor */
    printf ("serv Addr len: %d\n", broadcast_addr_len);
    printf ("client ip = %s   PORT: %d\n" ,inet_ntoa(broadcast_addr.sin_addr), ntohs(broadcast_addr.sin_port));

    /* sent to client. */
    while (1){
        bytes_sent = sendto(UDP_sockfd, cmd_udp, strlen(cmd_udp), 0,(struct sockaddr *)&broadcast_addr, (socklen_t)broadcast_addr_len);
        printf ("Bytes sent: %d\n", bytes_sent);
        usleep(1000000);
    }

    return 0;
}
