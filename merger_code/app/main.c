#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>

#include <errno.h>  /*Error number definition*/
#include <fcntl.h>  /*File Control Definition*/
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h> /*PPSIX Terminal Control Definition*/
#include <unistd.h>  /*Unix Standard Function Definitions*/
#include <pthread.h>
#include <sys/select.h>

#include "tcp_server.h"
#include "udp_broadcast.h"
#include "aes_cbc128.h"

pthread_t udp_thread_obj;
pthread_t tcp_thread_obj;

int main(void)
{
    pthread_create(&udp_thread_obj, NULL, udp_thread, NULL);
    pthread_create(&tcp_thread_obj, NULL, tcp_thread, NULL);

    pthread_join(udp_thread_obj, NULL);
    pthread_join(tcp_thread_obj, NULL);
    return 0;
}

