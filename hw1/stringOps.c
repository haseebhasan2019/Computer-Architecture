#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    char* s;
    for(int i=1; i<argc; i++)
    {
        s = argv[i];
        for(int j=0; j<strlen(s); j++)
        {
            if(s[j]=='a' || s[j]=='e'|| s[j]=='i'|| s[j]=='o'|| s[j]=='u'|| s[j]=='A'|| s[j]=='E'|| s[j]=='I'|| s[j]=='O' || s[j]=='U')
            {
                printf("%c",s[j]);
            }
        }
    }
}