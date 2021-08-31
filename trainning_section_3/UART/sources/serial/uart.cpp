#include "uart.h"

static const char* TAG = "uart";

UartConnection* UartConnection::uartInstance = nullptr; 

UartConnection::~UartConnection(void)
{

}

UartConnection* UartConnection::getInstance(const char*  device_file,
                                        int baudrate, int flow_ctrl,
                                        int databits, int stopbits, int parity)
{
    if (nullptr == uartInstance) {
        uartInstance = new UartConnection(device_file,
                                        baudrate, flow_ctrl,
                                        databits, stopbits, parity);
    }
    return uartInstance;
}

int UartConnection::UartSetAttribute(int speed, int flow_ctrl, int databits, int stopbits, int parity)
{
    struct termios options;
    static int speed_arr[] = {B115200, B19200, B9600, B4800, B2400, B1200, B300};
    static int name_arr[] = {115200, 19200, 9600, 4800, 2400, 1200, 300};

    if (tcgetattr(fd, &options) != 0) {
        m_printf(TAG, "SetupSerial 1");
        return -1;
    }

    /* Set the serial port input baud rate and output baud rate */
    for (unsigned int i = 0; i < (sizeof(speed_arr) / sizeof(int)); i++) {
        if (speed == name_arr[i]) {
            cfsetispeed(&options, speed_arr[i]);
            cfsetospeed(&options, speed_arr[i]);
        }
    }

    /* Modify the control mode to ensure that the program does not occupy the serial port */
    options.c_cflag |= CLOCAL;
    /* Modify the control mode, so that the input data can be read from the serial port */
    options.c_cflag |= CREAD;

    /* Set the data flow control */
    switch (flow_ctrl) {
        case 0:  // no flow control
            options.c_cflag &= ~CRTSCTS;
            break;

        case 1:  // Use hardware flow control
            options.c_cflag |= CRTSCTS;
            break;

        case 2:  // use software flow control
            options.c_cflag |= IXON | IXOFF | IXANY;
            break;
    }

    /* Set the data bit Block other flags */
    options.c_cflag &= ~CSIZE;
    switch (databits) {
        case 5:
            options.c_cflag |= CS5;
            break;
        case 6:
            options.c_cflag |= CS6;
            break;
        case 7:
            options.c_cflag |= CS7;
            break;
        case 8:
            options.c_cflag |= CS8;
            break;
        default:
            m_printf(TAG, "Unsupported data size\n");
            return -1;
    }

    /* Set the check digit */
    switch (parity) {
        case 'n':
        case 'N':  // no parity.
            options.c_cflag &= ~PARENB;
            options.c_iflag &= ~INPCK;
            break;

        case 'o':
        case 'O':  // set to odd parity
            options.c_cflag |= (PARODD | PARENB);
            options.c_iflag |= INPCK;
            break;

        case 'e':
        case 'E':  // set to even parity
            options.c_cflag |= PARENB;
            options.c_cflag &= ~PARODD;
            options.c_iflag |= INPCK;
            break;

        case 's':
        case 'S':  // set to space
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;
            break;

        default:
            m_printf(TAG, "Unsupported parity\n");
            return -1;
    }

    /* Set the stop bit */
    switch (stopbits) {
        case 1:
            options.c_cflag &= ~CSTOPB;
            break;

        case 2:
            options.c_cflag |= CSTOPB;
            break;

        default:
            m_printf(TAG, "Unsupported stop bits\n");
            return -1;
    }

    /* Modify the output mode, raw data output */
    options.c_oflag &= ~OPOST;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    // options.c_lflag &= ~(ISIG | ICANON);

    /* Set the waiting time and minimum receiving characters */
    options.c_cc[VTIME] = 1; /* Read a character waiting 1*(1/10)s */

    options.c_cc[VMIN] = 1; /* The minimum number of characters read is 1 */

    /* If the data overflow occurs, receive the data,
    but no longer read Refresh the received data but do not read */
    tcflush(fd, TCIFLUSH);

    /* Activate the configuration(set the modified termios data to the serial port) */
    if (tcsetattr(fd, TCSANOW, &options) != 0) {
        m_printf(TAG, "com set error!\n");
        return -1;
    }

    return 0;
}