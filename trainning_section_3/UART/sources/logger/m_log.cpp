#include "m_log.h"

#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <cctype>
#include <cstdint>

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  /*File Control Definition*/
#include <errno.h>  /*Error number definition*/

static int log_fd = 0;

void m_log_init(const char* logFile)
{
    /* Open file for work with */
    log_fd = open(logFile, O_WRONLY | O_CREAT | O_APPEND | O_ASYNC, S_IRWXU | S_IRWXG | S_IRWXO);
    if (log_fd < 0) {
        std::cout << "Logger initialize fail" << std::endl;
        exit(-1);
    }

    std::cout << "Logger initialize success. fd = " << log_fd << std::endl;
}

void m_printf(const char* tag, const char* format, ...)
{
    char aBuffer[1024];
    int size = 1024;

    va_list args;
    va_start(args, format);
    
    memset(aBuffer, 0, sizeof(aBuffer));
    sprintf(aBuffer, "[%s]: ", tag);
    vsnprintf(&aBuffer[strlen(aBuffer)], size, format, args);
    
    if (aBuffer[strlen(aBuffer) - 1] != '\n')
        aBuffer[strlen(aBuffer)] = '\n';
    va_end(args);

    /* show log */
    printf("%s", aBuffer);

    /* write message to log file */
    int ret = write(log_fd, aBuffer, strlen(aBuffer));
    if (ret < 0) {
        printf("failed to write to log.txt\n");
    }
}