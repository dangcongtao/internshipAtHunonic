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
    int UDP_sockfd = 0, err = 0, bytes_sent = 0, bytes_read = 0, opt =1, client_addr_len;
    char hello_fromserv[1024] = "hello this is message form server";
    char client_mssg[1024], *client_ip_string;
    socklen_t serv_addr_len;



    
    /* socket with UDP transport protocol */
    UDP_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   
    printf ("socket server: %d\n", UDP_sockfd);
    
    /* set address */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(IP_SERV);
    serv_addr.sin_port = htons(PORT);

    serv_addr_len = sizeof(serv_addr);
    printf ("serv Addr len: %d\n", serv_addr_len);
    
    /* bind */
    err = bind(UDP_sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (err != 0) {
        printf ("Bind Err: %s\n",  strerror(errno));
    }
   




    /* read ip address from client through UDP_sockfd */
    while (1) 
    {
        memset(client_mssg,0, sizeof(client_mssg));
        bytes_read = recvfrom(UDP_sockfd, client_mssg, sizeof(client_mssg), 0, (struct sockaddr *) &client_addr, &serv_addr_len);
        if (bytes_read > 0)
        {
            
            printf ("bytes read: %d\n",bytes_read);
            /* fork(); */
            bytes_read  = 1;
            client_addr_len = sizeof (client_addr);

            /* don't use it, will cause bug for send package. */
            /* err = getsockname(UDP_sockfd, (struct sockaddr*)&client_addr, &client_addr_len); */
            
            printf ("value read: %s\n", client_mssg);
        
            printf ("client ip = %s   PORT: %d\n" ,inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

            /* sent to client. */
            bytes_sent = sendto(UDP_sockfd, hello_fromserv, strlen(hello_fromserv), 0,(struct sockaddr *)&client_addr, client_addr_len);

            printf ("Bytes sent: %d\n", bytes_sent);
        }else {
            printf ("bytes read smaller than 0\n");
        }
    }    

    return 0;
}
