#include <stdio.h>

#include <stdlib.h>

#include <string.h>

void main(int argc  , char *argv[]){

	FILE *fp ;
    char path[200];
    char proc_name[200];
    int pid =1; /* get pid from keyboard */

    sprintf(path, "/proc/%d/comm",pid);

    /* printf("\npath: %s\n", path); */
    fp = fopen(path, "r");

    fgets(proc_name, 200, fp);
    printf("\nprocess name: %s\n", proc_name);
    fclose(fp);
}