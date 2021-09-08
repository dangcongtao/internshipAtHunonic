#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>
#include <string.h>

/* ----------------------------------------------------------------------------
 * Named pipes are special file that are used by processes to communicate
 *
 * The name of the file is define in PIPE_NAME and it will persist after
 * termination, it can be reused.
 *
 * Opening a named pipe is a blocking call, until both ends are connected.
 * This behavior can be override with O_NDELAY in open(). A process writting
 * a pipe with no reader will be signaled with SIGPIPE.
 *
 * File permissions in mknod are added with the current user permission.
 * Therfore using umask(0) will clean the inherited permission.
 *
 */

#define PIPE_NAME "./MyPipe"
#define PIPE_NAME2 "./MyPipe2"
#define PROC_MQTT "b"
int SIZE_BUFF = 1024;
int loop = 1;
int fd[2] = {0};
char *MESSAGE = "Hello from A";
char buffer[1024];
int have_data = 0;

// Process id
pid_t child_pid;


/* no bugs */
int getProcIdByName(char *procName)
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
                char cmdPath[SIZE_BUFF];
				strcpy(cmdPath, "/proc/");
				strcat(cmdPath, dirp->d_name );
				strcat(cmdPath, "/cmdline");
				
                int cmdFile = open(cmdPath, O_RDONLY);
                char cmdLine[SIZE_BUFF];
				memset(cmdLine, 0 ,SIZE_BUFF);

                read(cmdFile, cmdLine, SIZE_BUFF);
				/* printf ("path: %s\n", cmdPath); */
                
                if (strlen(cmdLine) > 0)
                {
					char result[SIZE_BUFF];
					char temp[SIZE_BUFF];
					
					memset(result, 0, SIZE_BUFF);
					memset(temp, 0, SIZE_BUFF);
					

                    // Keep first cmdline item which contains the program path
					strcpy(temp, strtok(cmdLine, " "));
					int pos1 = 0, pos2 = strlen(temp);
					/* printf ("temp: %s\n", temp); */
					
                    /* bug in here */
					for (int i = pos2 ; i >= 0 ; i--) {
                        if (temp[i] == '/'){
							pos2 = i + 1;
                            i = -1;
                        }
                    }
                    if (pos2 >= strlen(temp)){
						pos2 = 0;
					}
					
					for (int i = (pos2); i < strlen(temp); i ++) {
						result[pos1] = cmdLine[i];
						pos1 = pos1 + 1;
					}
                    /* printf ("result2: %s\n", result); */
					
                    // Compare against requested process name
                    if (strcmp (procName, result) == 0){
                        pid = id;
						printf ("PID found: %d\n", id);
					}
                }
            }
        }
    }
    closedir(dp);
    return pid;
}

void sig_int_handler (int signo) {
    if (read(fd[0], buffer, 128) > 0){
        have_data = 1;
        printf("Received: %s\n", buffer);
    }

	if (have_data == 1){

        write(fd[1], MESSAGE, strlen(MESSAGE) +1 );
        printf ("sent\n");
        kill(getProcIdByName(PROC_MQTT), SIGINT);
    }else {
        printf("data empty\n");
    }
}


int main(int argc, const char *argv[]){

    int ch;

	/* Creating the pipe */
	umask(0);
	if(mknod(PIPE_NAME, S_IFIFO | 0660, 0) == -1){
		if(errno != EEXIST){
			perror("Cannot create the pipe");
			exit(EXIT_FAILURE);
		}
		else
			printf("Using existing file: %s\n", PIPE_NAME);
	}
    if(mknod(PIPE_NAME2, S_IFIFO | 0660, 0) == -1){
		if(errno != EEXIST){
			perror("Cannot create the pipe");
			exit(EXIT_FAILURE);
		}
		else
			printf("Using existing file: %s\n", PIPE_NAME2);
	}
    signal(SIGINT, sig_int_handler);

    printf ("opening pipe... \n");
    fd[0] = open(PIPE_NAME, O_RDONLY);
    if (fd[0] >= 0 ) {
		printf ("opening %s successed...\n", PIPE_NAME);
	}else {
		printf ("open %s Err: %s\n", PIPE_NAME, strerror(errno));
	}

    fd[1] = open(PIPE_NAME2, O_WRONLY);
    if (fd[1] >= 0 ) {
        printf ("opening %s successed...\n", PIPE_NAME);
    }else {
        printf ("open %s Err: %s\n", PIPE_NAME, strerror(errno));
    }
    
    /* Loop util get signal */
	printf ("press Q to quit\n");
	do 
	{
		ch = getchar();
	} while (ch!='Q' && ch != 'q' );
	printf ("out of loop\n");
    
    if (close(fd[0]) < 0) {
		printf ("close fd0 err: %s\n", strerror(errno));
	}
	if (close(fd[1]) < 0) {
		printf ("close fd1 err: %s\n", strerror(errno));
	}

	return 0;
}