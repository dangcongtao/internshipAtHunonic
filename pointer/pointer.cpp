#include <iostream>
#include<string.h>
using namespace std;

void nhiphan(float n)
{
    for(int i=0,*temp=(int *)&n;i<sizeof(n)*8;i++,(*temp)<<=1)
        printf("%d",*temp>=0);
}

int main()
{
    char * temp;

    char a[10];
    char b[20];
    scanf("%[a-zA-Z0-9 ]",a);

    temp = (char *) malloc(sizeof(char) * strlen(a));
    strcpy(temp, a);

    cin.ignore();
    scanf("%[a-zA-Z0-9 ]",b);
    // puts(a);
    // puts(b);
    // puts(temp);
    free(a);
    printf("%s", temp);
} 


