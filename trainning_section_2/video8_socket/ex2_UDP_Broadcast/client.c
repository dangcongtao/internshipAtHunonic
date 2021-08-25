#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h> /* for strerr() */

int main (int argc, char *argv[]) {

    int sockfd;
    struct sockaddr_in broadcast_addr, serv_addr, client_addr;
    int addr_len = sizeof(broadcast_addr), counter = 0, broadcast_permission = 1;
    char buff[1024];

    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0){
        printf("socket Err: %d\n", sockfd);
    }

    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (void *)&broadcast_permission, (socklen_t)sizeof(broadcast_permission));
   
    client_addr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.0.255", &client_addr.sin_addr.s_addr);
    client_addr.sin_port = htons(5000);

    counter = bind(sockfd, (struct sockaddr*)&client_addr, (socklen_t)sizeof(client_addr));
    if (counter < 0){
        printf ("bind Err: %d \t %s\n", counter, strerror(errno));
    }

    counter = recvfrom (sockfd, &buff, sizeof(buff), 0, (struct sockaddr*)&broadcast_addr, &addr_len);
    printf ("bytes received: %d\n", counter);
    printf ("received: %s\n", buff);
    return 0;
}