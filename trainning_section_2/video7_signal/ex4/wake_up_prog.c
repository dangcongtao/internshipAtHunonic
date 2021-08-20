#include<stdio.h>
#include<signal.h>


int main (int argc, char *argv[])
{
	/* PID'll change so ps -a to catch and change the PID. */
	int pid_sleeping_proc = 8320;

	kill(pid_sleeping_proc, SIGINT);
	return 0;
}
