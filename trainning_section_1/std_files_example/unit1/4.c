#include<stdio.h>
#include <dirent.h>
int main (int argc, char* argv[]) {
    FILE *file;
    char charfile;

    file = fopen(argv[1], "r");
    
    charfile = (char)fgetc(file) ;
    
    while (charfile != EOF)
    {
        printf("%c",charfile);
        charfile = (char)fgetc(file);
    }
    printf("\n");
    fclose(file);
    
    struct dirent dir;

    dir.


    return 0;
}