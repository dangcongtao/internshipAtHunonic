#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main () {
    char buf[100];

    int fd = open("fast_file.txt", O_RDONLY);
    int flag = fcntl(fd, F_GETFL, 0);
    
    flag &= ~O_NONBLOCK;
    fcntl(fd, F_SETFL, flag);

    int ret = read(fd, buf, 100);

    printf ("buf in fast file: %s\n%d\n", buf, ret);
    return 0;
}