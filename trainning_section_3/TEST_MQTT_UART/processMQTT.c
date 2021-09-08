/* idea to buil MQTT */

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <ctype.h>
#include <MQTTAsync.h>


#if !defined(_WIN32)
#include <unistd.h>
#else
#include <windows.h>
#endif

#if defined(_WRS_KERNEL)
#include <OsWrapper.h>
#endif


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


#define ADDRESS     "127.0.0.1"
#define CLIENTID    "ExampleClientSub"
#define TOPIC       "MQTT Examples"
#define PAYLOAD     "Hello World! from sub app haha"
#define QOS         0
#define TIMEOUT     10000L

#define PIPE_NAME "./MyPipe"
#define PIPE_NAME2 "./MyPipe2"
#define SIZE_BUFF 1024
#define MSG " HELLO"
#define PROC_UART "a"
int loop = 1;
int fd[2] = {0};
char buffer[1024] = {0};


// Process id
pid_t child_pid;

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
					
                    if (strcmp (procName, result) == 0){
                        pid = id;
						/* printf ("result: %s\n", result); */
					}
                }
            }
        }
    }
    closedir(dp);
    return pid;
}


int disc_finished = 0;
int subscribed = 0;
int finished = 0;
MQTTAsync client;

void connlost(void *context, char *cause)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	int rc;

	printf("\nConnection lost\n");
	if (cause)
		printf("     cause: %s\n", cause);

	printf("Reconnecting\n");
	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start connect, return code %d\n", rc);
		finished = 1;
	}
}


int msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{
	int rc;
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: %.*s\n", message->payloadlen, (char*)message->payload);
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);

	MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
	MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
	opts.context = client;
	pubmsg.payload = PAYLOAD;
	pubmsg.payloadlen = (int)strlen(PAYLOAD);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;
	if ((rc = MQTTAsync_sendMessage(client, "PUB", &pubmsg, &opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start sendMessage, return code %d\n", rc);
	}

    return 1;
}

void onDisconnectFailure(void* context, MQTTAsync_failureData* response)
{
	printf("Disconnect failed, rc %d\n", response->code);
	disc_finished = 1;
}

void onDisconnect(void* context, MQTTAsync_successData* response)
{
	printf("Successful disconnection\n");
	disc_finished = 1;
}

void onSubscribe(void* context, MQTTAsync_successData* response)
{
	printf("Subscribe succeeded\n");
	subscribed = 1;
}

void onSubscribeFailure(void* context, MQTTAsync_failureData* response)
{
	printf("Subscribe failed, rc %d\n", response->code);
	finished = 1;
}


void onConnectFailure(void* context, MQTTAsync_failureData* response)
{
	printf("Connect failed, rc %d\n", response->code);
	finished = 1;
}




void onSendFailure(void* context, MQTTAsync_failureData* response)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;
	int rc;

	printf("Message send failed token %d error code %d\n", response->token, response->code);
	opts.onSuccess = onDisconnect;
	opts.onFailure = onDisconnectFailure;
	opts.context = client;
	if ((rc = MQTTAsync_disconnect(client, &opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start disconnect, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}
}

void onSend(void* context, MQTTAsync_successData* response)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;
	int rc;

	printf("Message with token value %d delivery confirmed\n", response->token);
	opts.onSuccess = onDisconnect;
	opts.onFailure = onDisconnectFailure;
	opts.context = client;
	if ((rc = MQTTAsync_disconnect(client, &opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start disconnect, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}
}


void onConnect(void* context, MQTTAsync_successData* response)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
	MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
	int rc;

	printf("Successful connection\n");

	printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
           "Press Q<Enter> to quit\n\n", TOPIC, CLIENTID, QOS);
	opts.onSuccess = onSubscribe;
	opts.onFailure = onSubscribeFailure;
	opts.context = client;
	if ((rc = MQTTAsync_subscribe(client, TOPIC, QOS, &opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start subscribe, return code %d\n", rc);
		finished = 1;
	}
}


void sig_int_handler (int signo) {
	printf ("recev Signal\n");

	memset(buffer, 0 , 1024);
	read(fd[1], buffer, 1024);
	printf ("read: %s\n", buffer);
}

void send_message (char *msg) {
	write(fd[0],msg, strlen(msg));
	printf("Sent: %s\n", msg);
	kill(getProcIdByName(PROC_UART), SIGINT);
}

int main(int argc, const char *argv[]){

	int ch = 0;



	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;
	int rc;
	int ch;

	if ((rc = MQTTAsync_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL))
			!= MQTTASYNC_SUCCESS)
	{
		printf("Failed to create client, return code %d\n", rc);
		rc = EXIT_FAILURE;
		/* goto exit; */
	}

	if ((rc = MQTTAsync_setCallbacks(client, client, connlost, msgarrvd, NULL)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to set callbacks, return code %d\n", rc);
		rc = EXIT_FAILURE;
		/* goto destroy_exit; */
	}

	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;
	conn_opts.onSuccess = onConnect;
	conn_opts.onFailure = onConnectFailure;
	conn_opts.context = client;
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start connect, return code %d\n", rc);
		rc = EXIT_FAILURE;
		/* goto destroy_exit; */
	}


	/* Creating the pipe */
	umask(0);
	if(mknod(PIPE_NAME, S_IFIFO | 0660, 0) == -1){
		if(errno != EEXIST){
			perror("Cannot create the pipe");
			exit(EXIT_FAILURE);
		}
		else
			printf("Using existing file\n");
	}
	if(mknod(PIPE_NAME2, S_IFIFO | 0660, 0) == -1){
		if(errno != EEXIST){
			perror("Cannot create the pipe");
			exit(EXIT_FAILURE);
		}
		else
			printf("Using existing file\n");
	}

	printf ("opening pipe...\n");
	fd[0] = open(PIPE_NAME, O_WRONLY);
	if (fd[0] >= 0 ) {
		printf ("opening %s successed...\n", PIPE_NAME);
	}else {
		printf ("open %s Err: %s\n", PIPE_NAME, strerror(errno));
	}

	fd[1] = open(PIPE_NAME2, O_RDONLY);
	if (fd[1] >= 0 ) {
		printf ("opening %s successed...\n", PIPE_NAME2);
	}else {
		printf ("open %s Err: %s\n", PIPE_NAME2, strerror(errno));
	}

	/* init */
	if (signal(SIGINT, sig_int_handler) == SIG_ERR) {
		printf ("Signal fail: %s\n", strerror(errno));
	}

	printf ("Loop until exit key");
	do 
	{
		send_message(MSG);
		usleep(5000);
		loop ++;

		if (loop == 10) {
			printf ("press Q to quit\n");
			ch = getchar();
		}

	} while (ch!='Q' && ch != 'q' );
	printf ("out of loop\n");

	
	/* exitting proc */
	if (close(fd[1]) < 0) {
		printf ("close fd1 err: %s\n", strerror(errno));
	}

	if (close(fd[0]) < 0) {
		printf ("close fd0 err: %s\n", strerror(errno));
	}
	
	return 0;
}
