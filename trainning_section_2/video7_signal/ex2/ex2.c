#include<stdio.h>
#include<signal.h>

int main (int argc, char *argv[])
{
	/* create a mask */
	sigset_t my_sign_set;

	sigemptyset(&my_sign_set);
	sigaddset(&my_sign_set, SIGINT);
	
	/* block signal INT of process */	
	sigprocmask(SIG_BLOCK, &my_sign_set, NULL);

	/* to check signal */
	while (1);

	return 0;
}
