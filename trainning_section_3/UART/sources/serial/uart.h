#ifndef _UART_H_
#define _UART_H_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstdint>

#include <errno.h>  /*Error number definition*/
#include <fcntl.h>  /*File Control Definition*/
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h> /*PPSIX Terminal Control Definition*/
#include <unistd.h>  /*Unix Standard Function Definitions*/
#include <pthread.h>
#include <sys/select.h>
#include <string>

#include "m_log.h"

class UartConnection {
private:
    static UartConnection *uartInstance;
    int fd;
    pthread_t thread_tx;
    pthread_t thread_rx;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    bool error;
    std::string message;


    UartConnection(void)
    {
    }

    UartConnection(const char* portDevFile,
                            int baudrate, int flow_ctrl,
                            int databits, int stopbits, int parity)
    {
        /* Open /dev/tty* file for work with */
        fd = open(portDevFile, O_RDWR | O_NOCTTY | O_NDELAY);
        if (fd < 0) {
            m_printf("UART", "open uart port error\n");
            close(fd);
            exit(-1);
        }

        /* Restore the serial port is blocked */
        int ret  = fcntl(fd, F_SETFL, 0);
        if (ret < 0) {
            m_printf("UART", "fcntl failed!\n");
            close(fd);
            exit(-1);   
        } else {
            m_printf("UART", "fcntl=%d\n", ret);
        }

        /* Test whether it is a terminal device */
        if (0 == isatty(STDIN_FILENO)) {
            m_printf("UART", "standard input is not a terminal device\n");
            close(fd);
            exit(-1);
        } else {
            m_printf("UART", "isatty success!\n");
        }

        /* Set serial port attributes */
        if (UartSetAttribute(baudrate, flow_ctrl, databits, stopbits, parity) < 0) {
            m_printf("UART", "set uart attribute error\n");
            close(fd);
            exit(-1);
        }
    }


public:
    ~UartConnection(void);
    static UartConnection* getInstance(const char*  device_file,
                                        int baudrate, int flow_ctrl,
                                        int databits, int stopbits, int parity);
    int UartSetAttribute(int baudrate, int flow_ctrl,
                        int databits, int stopbits, int parity);
};

#endif /* _UART_H_ */
