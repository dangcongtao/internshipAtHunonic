#include<stdio.h>
#include<signal.h>

void sig_handler (int signo)
{
	printf ("signal handler was called!!\n");
}

int main (int argc, char *argv[])
{
	signal(SIGINT, sig_handler);
	
	while (1);
	return 0;
}
