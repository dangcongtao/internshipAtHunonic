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

#include "system_typedef.h"
#include "aes_cbc128.h"

#define PORT 8888
#define MAX_LEN_UDP_MSG 1024

char* cmd_udp = "{\"gateway\":1, \"brand\":\"HUNONIC\"}";
static int have_request_send_udp = 1;
static char udp_message_to_send[MAX_LEN_UDP_MSG];
static uint32_t len_msg_udp = MAX_LEN_UDP_MSG;

void udp_send_data(char* raw_message, int len)
{
    /* encode data to send */
    aes_cbc128_init((uint8_t *)DEFAULT_AES_KEY, (uint8_t *)DEFAULT_AES_IV);
    uint32_t aes_encrypt_result = aes_cbc128_encrypt((uint8_t *)raw_message, strlen(raw_message), (uint8_t*)udp_message_to_send, (size_t *)&len_msg_udp);
    if (aes_encrypt_result != AES_SUCCESS) {
        printf("Encode fail,error-code: %d\n", aes_encrypt_result);
        return;
    }

    have_request_send_udp = 1;
}

void set_request_send_udp(void)
{
    have_request_send_udp = 1;
}

void clear_request_send_udp(void)
{
    have_request_send_udp = 0;
}

void* udp_thread (void *args) {

    (void)args;

    struct sockaddr_in broadcast_addr;
    int UDP_sockfd = 0, bytes_sent = 0, broadcast_addr_len;
    int broadcast_permission = 1;

    /* socket with UDP transport protocol */
    UDP_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   /* set option SO_BROADCAST for socket. */
    setsockopt(UDP_sockfd, SOL_SOCKET, SO_BROADCAST, (void*)&broadcast_permission, sizeof(broadcast_permission));

    /* set address to send to this addr */
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_addr.s_addr = INADDR_BROADCAST;
    broadcast_addr.sin_port = htons(PORT);
    broadcast_addr_len = sizeof(broadcast_addr);

    broadcast_addr_len = sizeof (broadcast_addr);
    
    /* print infor */
    printf ("serv Addr len: %d\n", broadcast_addr_len);
    printf ("client ip = %s   PORT: %d\n" ,inet_ntoa(broadcast_addr.sin_addr), ntohs(broadcast_addr.sin_port));

    udp_send_data(cmd_udp, strlen(cmd_udp));

    /* sent to client. */
    while (1) {
        if (have_request_send_udp) {
            /* send */
            bytes_sent = sendto(UDP_sockfd, udp_message_to_send, len_msg_udp, 0,(struct sockaddr *)&broadcast_addr, (socklen_t)broadcast_addr_len);
            printf ("Bytes sent: %d\n", bytes_sent);
            usleep(1000000);
        }
    }
}
