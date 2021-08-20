/* program to test
 * check pid number of process parent and child.
 *
 *
 * */


#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main (int argc, char*argv[])
{
	int pid = fork();


	if (pid == 0 )
	{
		printf ("pid == 0 \n");
	}
	else 
	{
		printf ("%d\n", pid);
	}

	return 0;
}
