#include<stdio.h>
#include<signal.h>
#include<unistd.h>


int main ()
{
	sigset_t my_sign_set, pendding;

	/* block signal SIGNINT */
	sigemptyset(&my_sign_set);
	sigaddset(&my_sign_set, SIGINT);
	
	sigprocmask(SIG_BLOCK, &my_sign_set, NULL);
	// signal(SIGINT, my_sig);
	
	while(1)
	{

		/* check pending */
		sigpending (&pendding);

		if (sigismember(&pendding, SIGINT) == 1)
		{
			printf ("\nSIGINT in the pendding..! \n");
			sigprocmask(SIG_UNBLOCK, &my_sign_set, NULL);
		}else {

		}
	}
	

	return 0;
}
