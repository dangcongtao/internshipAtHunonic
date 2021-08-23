/*
 * program to print alleviroment variable.
 *
 * */

#include<stdio.h>
#include<stdlib.h>


int main(int argc, char *argv[])
{
	extern char **environ; 
	int i =  0;
	
	while(environ[i] != NULL) {
		printf ("var Envir %d: %s\n", i, environ[i]);
		i = i + 1;
	} 
	
	/* using: char* getenv(); */
	printf ("\nuser name: %s\n", getenv("USERNAME"));
	return 0;
}
