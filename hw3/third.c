#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    //Declare variables
    unsigned short* num = malloc(sizeof(unsigned short));
    *num = atoi(argv[1]);
    int front = 0;
    int back = 15;
    int isPalindrome = 1;

    //Parse
    while (front < 16) 
    {
        if ( ((*num >> front) & 1U) == ((*num >> back) & 1U) )
        {
            front++;
            back--;
        }
        else 
        {
            isPalindrome = 0;
            break;
        }
    }

    //Output
    if (isPalindrome == 1)
        printf("Is-Palindrome\n");
    else
        printf("Not-Palindrome\n");

    //Free pointer
    free(num);
}
