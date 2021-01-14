#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    //Declare Variables
    unsigned short* num = malloc(sizeof(unsigned short));
    *num = atoi(argv[1]);
    int ones = 0;
    int pairs = 0;

    //Parse
    for (int i = 0; i < 16; i++) 
    {
        if ( ((*num >> i) & 1U) == 1) 
        {
            ones++;
            if ( ((*num >> (i+1)) & 1U) == 1) 
            {
                ones++;
                pairs++;
                i++;
            }
        }
    }
    //Output
    if(ones % 2 == 0)
        printf("Even-Parity\t%d\n", pairs);
    else
        printf("Odd-Parity\t%d\n", pairs);
    //Free pointer
    free(num);
}
