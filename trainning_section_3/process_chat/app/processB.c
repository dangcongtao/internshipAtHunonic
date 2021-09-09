#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <ctype.h>
#include <pthread.h>

#define STRING_SIZE 1024
#define SEND_PIPE "./pipe2"
#define RECEIVE_PIPE "./pipe1"
int fd[2] = {0};


void *thread_typing (void *arg) {
    char string[STRING_SIZE] = {0};
	do{
		memset(string, 0, STRING_SIZE);
		gets(string);
		write(fd[0], string, strlen(string));
		printf ("-Message sent: %s\n", string);
	}while (1);
	printf ("typing is out of loop\n");
    return arg;
}

void *thread_listening (void *arg) {
	char buff[STRING_SIZE] = {0};
    do{
		memset(buff, 0,STRING_SIZE);
		read(fd[1], buff, STRING_SIZE);
		printf ("-Received: %s\n", buff);
    }while (1);
	printf ("listen is out of loop\n");
    return arg;
}

int main () {

    /* initialize state */
    pthread_t typing, listening;

    umask(0);
	if(mknod(SEND_PIPE, S_IFIFO | 0660, 0) == -1){
		if(errno != EEXIST){
			perror("Cannot create the pipe");
			exit(EXIT_FAILURE);
		}
		else
			printf("Using existing file\n");
	}
	if(mknod(RECEIVE_PIPE, S_IFIFO | 0660, 0) == -1){
		if(errno != EEXIST){
			perror("Cannot create the pipe");
			exit(EXIT_FAILURE);
		}
		else
			printf("Using existing file\n");
	}

	printf ("opening pipe...\n");
	fd[0] = open(SEND_PIPE, O_WRONLY);
	if (fd[0] >= 0 ) {
		printf ("opening %s successed...\n", SEND_PIPE);
	}else {
		printf ("open %s Err: %s\n", SEND_PIPE, strerror(errno));
	}

	fd[1] = open(RECEIVE_PIPE, O_RDONLY);
	if (fd[1] >= 0 ) {
		printf ("opening %s successed...\n", RECEIVE_PIPE);
	}else {
		printf ("open %s Err: %s\n", RECEIVE_PIPE, strerror(errno));
	}
    printf ("open success\n");

    pthread_create(&typing, NULL, thread_typing, NULL );
    pthread_create(&listening, NULL, thread_listening, NULL );
    
    pthread_join(listening, NULL);
    pthread_join(typing, NULL);
    

    /* state 1 
    while (loop == 1) {

    }*/

    /* quit state */
    if (close(fd[1]) < 0) {
		printf ("close fd1 err: %s\n", strerror(errno));
	}

	if (close(fd[0]) < 0) {
		printf ("close fd0 err: %s\n", strerror(errno));
	}
    return 0;
}