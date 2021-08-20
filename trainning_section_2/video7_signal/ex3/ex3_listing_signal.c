#include<stdio.h>
#include<signal.h>

int main (int argc, char *argv[])
{
	sigset_t my_sig_set;
	
	/* turn on all bit of the mask table */
	sigemptyset(&my_sig_set);
	sigfillset(&my_sig_set);
	

	/* check the signal num */
	for (int i = 0 ; i < 255 ; i ++) 
	{
		if (sigismember(&my_sig_set, i) == 1){
			printf ("number signal: %d\n", i);
		}
	}
	return 0;
}
