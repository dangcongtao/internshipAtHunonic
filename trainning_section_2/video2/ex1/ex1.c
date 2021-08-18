#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main (int argc, char *argv[])
{
	printf ("read a file at any point.\nsyntax:my_prog file_name num_pos num_from\n\n");
	if (argc != 4)
	{
		perror("incorrect syntax\n");
		return -1;
	}else
	{
		char *char_file = (char*)malloc(sizeof(char)*2);
		int file = open(argv[1], O_RDONLY);
		
		lseek(file, atoi(argv[2]),atoi(argv[3]));
		while (read(file,char_file,1) != 0 )
		{
			printf ("%s", char_file);
		}

		/* free malloc, need to check out */
		free(char_file);
		char_file = NULL;
		close (file);
	}
	return 0;
}
