#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include "mqtt/async_client.h"

#include <sys/mman.h> /* for mem mapping. */
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <errno.h>
#include <errno.h>

int main () {
    int shm_fd = open("file_shm", O_RDONLY, 0666);
    int is_err = ftruncate(shm_fd, 4096);
    void *shm_ptr = mmap(0,4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if (shm_fd < 0){
        std::cout << "open fail: " << strerror(errno) << std::endl;
    }
    if ( is_err != 0 ) {
        std::cout << "ftruncate Err: " << strerror(errno) << std::endl;
    }

    if (shm_ptr == MAP_FAILED) {
        std::cout << "maping fail: " << strerror(errno) << std::endl;
    }


    /* procces */
    std::cout<< "string: "  << (char*)shm_ptr << std::endl; 


    /* avoid meme leak 
    if (munmap(0,4096) != 0) {
        std::cout<< "Unmap Err.\n";
    }
    */
    if (shm_unlink("file_shm") != 0) {
        std::cout << "Unlink Err.\n";
    }

    return 0;
}