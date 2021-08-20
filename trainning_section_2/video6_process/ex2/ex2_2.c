#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

int main (int argc, char*argv[])
{
	int a = open("file_temp.txt", O_WRONLY);

	int var_1 = 1, var_2 = 2;
	
	int pid = fork();
	
	if (pid != 0) 
	{
		/* parent process */
		while (1)
		{
			printf ("pid != 0\n");
		}
	}
	else 
		while(1)
			printf ("pid == 0\n");

	return 0;
}
