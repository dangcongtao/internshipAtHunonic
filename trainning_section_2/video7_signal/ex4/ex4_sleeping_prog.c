#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>

int main (int argc, char *argv[])
{
	sigset_t my_sig_set, pendding;
	int i = 1;

	
	sigemptyset(&my_sig_set);
	sigaddset(&my_sig_set, SIGINT);
	sigprocmask(SIG_BLOCK, &my_sig_set, NULL);

	/* sleeping forever */
	while (i){
		
		sleep(0.3);

		sigpending(&pendding);
		if (sigismember(&pendding, SIGINT) == 1){
			// sigprocmask(SIG_UNBLOCK, &my_sig_set, NULL);
			i = 0;
			printf("\e[1:1H\e[2J");
			printf("\nwoke up!!!\n");
		}

	}
	
	printf ("\nprogram will end\n");
	return 0;
}
