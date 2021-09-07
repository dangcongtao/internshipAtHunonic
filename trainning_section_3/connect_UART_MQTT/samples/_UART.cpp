#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include <signal.h>
#include "mqtt/async_client.h"

#include <sys/mman.h> /* for mem mapping. */
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <err.h>

#include <dirent.h>
#include <fstream>

const char *SUB_NAME_PROC = "subcribe";
const char *MESSAGE_SEND = "hello from UART";

int shm_fd_recever = shm_open("broker_to_UART", O_RDONLY, 0666);
void *ptr_recv = mmap(0,4096, PROT_READ, MAP_SHARED, shm_fd_recever, 0);

int shm_fd_sendder = shm_open("UART_to_broker", O_CREAT | O_RDWR, 0666);
int is_err = ftruncate(shm_fd_sendder,4096);
void *ptr_sendder = mmap(0,4096, PROT_WRITE, MAP_SHARED, shm_fd_sendder, 0);



int getProcIdByName(std::string procName)
{
    int pid = -1;

    // Open the /proc directory
    DIR *dp = opendir("/proc");
    if (dp != NULL)
    {
        // Enumerate all entries in directory until process found
        struct dirent *dirp;
        while (pid < 0 && (dirp = readdir(dp)))
        {
            // Skip non-numeric entries
            int id = atoi(dirp->d_name);
            if (id > 0)
            {
                // Read contents of virtual /proc/{pid}/cmdline file
                std::string cmdPath = std::string("/proc/") + dirp->d_name + "/cmdline";
                std::ifstream cmdFile(cmdPath.c_str());
                std::string cmdLine;
                std::getline(cmdFile, cmdLine);
                if (!cmdLine.empty())
                {
                    // Keep first cmdline item which contains the program path
                    size_t pos = cmdLine.find('\0');
                    if (pos != std::string::npos)
                        cmdLine = cmdLine.substr(0, pos);
                    // Keep program name only, removing the path
                    pos = cmdLine.rfind('/');
                    if (pos != std::string::npos)
                        cmdLine = cmdLine.substr(pos + 1);
                    // Compare against requested process name
                    if (procName == cmdLine)
                        pid = id;
                }
            }
        }
    }

    closedir(dp);

    return pid;
}



void recev_message () {

    if (shm_fd_recever < 0){
        std::cout << "open fail: " << strerror(errno) << std::endl;
        return;
    }
    
    if (ptr_recv == MAP_FAILED) {
        std::cout << "maping fail: " << strerror(errno) << std::endl;
        return;
    }


    /* printf message recev */
    std::cout<< "Message Received: "  << (char*)ptr_recv << std::endl; 

    if (munmap(0,4096) != 0) {
        std::cout<< "Unmap Err.\n";
        return;
    }
    return;
}

void send_message (const char *MESSAGE) {
    

    if (shm_fd_sendder < 0){
        std::cout << "open fail: " << strerror(errno) << std::endl;
        return;
    }
    if (is_err != 0) {
        std::cout << "ftruncate fail: " << strerror(errno) << std::endl;
        return;
    }
    
    if (ptr_sendder == MAP_FAILED) {
        std::cout << "mapping fail: " << strerror(errno) << std::endl;
        return;
    }

    /* send message */
    strcpy((char*)ptr_sendder, MESSAGE);

    /* send signal */
    kill(getProcIdByName(SUB_NAME_PROC), SIGINT);
    /* unmap */
    if (munmap(0,4096) != 0) {
        std::cout<< "Unmap Err.\n";
        return;
    }
    return;
}




void *recev_thread (void *) {

    if (shm_fd_recever < 0){
        std::cout << "open fail: " << strerror(errno) << std::endl;
        return NULL;
    }
    
    if (ptr_recv == MAP_FAILED) {
        std::cout << "maping fail: " << strerror(errno) << std::endl;
        return NULL;
    }


    /* printf message recev */
    std::cout<< "Message Received: "  << (char*)ptr_recv << std::endl; 

    /* send signal */
    kill(getProcIdByName(SUB_NAME_PROC), SIGINT);

    if (munmap(0,4096) != 0) {
        std::cout<< "Unmap Err.\n";
        return NULL;
    }
    return NULL;
}

void sendder_thread () {
    char *MESSAGE = (char*)"hello from UART";

    if (shm_fd_sendder < 0){
        std::cout << "open fail: " << strerror(errno) << std::endl;
        return;
    }
    if (is_err != 0) {
        std::cout << "ftruncate fail: " << strerror(errno) << std::endl;
        return;
    }
    
    if (ptr_sendder == MAP_FAILED) {
        std::cout << "mapping fail: " << strerror(errno) << std::endl;
        return;
    }

    /* send message */
    strcpy((char*)ptr_sendder, MESSAGE);


    /* unmap */
    if (munmap(0,4096) != 0) {
        std::cout<< "Unmap Err.\n";
        return;
    }
    return;
}







/* Signal handler */
void handler_SIGINT (int signo) {
    recev_message();
    send_message(MESSAGE_SEND);
}

int main () {
    
    signal(SIGINT, handler_SIGINT);
    while (std::tolower(std::cin.get()) != 'q');

    if (shm_unlink("broker_to_UART") != 0) {
        std::cout << "Unlink Err.\n";
    }
    if (shm_unlink("UART_to_broker") != 0) {
        std::cout << "Unlink Err.\n";
    }
    return 0;
}