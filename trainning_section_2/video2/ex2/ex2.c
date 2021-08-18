#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <dirent.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int main (int argc, char *argv[])
{
	/*
	 * Syntax: PROGRAM_NAME FILE_NAME 
	 * print infor of a file: NAME, SIZE, MODIFY_TIME.
	 *
	 */

	
	/* SYNTAX: DIR *opendir();
	 *
	 * open directory stream, make sure that *dirp is readable
	 * that doesn't cause any err by using readdir().
	 * nottice: dirp is a directory stream obj
	*/
	DIR *dirp = opendir(argv[1]);
	if (dirp == NULL) 
	{
		perror("opendir err");
		return -1;
	}
	
	printf ("open folder ok\n");

	/* SYNTAX:struct dirent *readdir(DIR dirp);
	 * 
	 * read folder 
	*/
	struct dirent *folder;
	struct stat folder_stat;
	
	
	while  ((folder = readdir(dirp)) != NULL )
	{
		char path[255];
		struct tm time; /* use to convert st_mmin to day, month, .. */
		memset(path, 0,sizeof(path));

		printf ("file name: %s\n",folder->d_name);
		
		/* return 4 if a directory, 8 if a regular file */
		if (folder->d_type == 4)
			printf ("file type: folder\n");
		if (folder->d_type == 8)
			printf ("file type: regular file\n");

		/* get information of files in folder argv[1] by using stat(); */
		strcpy(path, argv[1]);
		strcat(path, folder->d_name);
		stat(path, &folder_stat);

		printf ("inode number by dirent: %lu\n",folder->d_ino);
		printf ("inode number by stat__: %lu\n",folder_stat.st_ino);
		
		time = *(gmtime( /*( time_t )*/ (&folder_stat.st_ctim.tv_sec) ));
		printf ("file size: %llubytes\n", (unsigned long long)folder_stat.st_size);
		printf ("file last modify time: %d/%d/%d\n\n", time.tm_mday, time.tm_mon, time.tm_year + 1900);
		
	}
	 

	
	if (closedir(dirp) == -1) 
	{
		perror("closedir err");
		return -1;
	}
	free(folder);
	folder = NULL;
	
	return 0;
}
