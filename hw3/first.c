#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int main(int argc, char* argv[])
{
    FILE * file = fopen (argv[1], "r");

    //First line 
    unsigned short* num = malloc(sizeof(unsigned short));
    fscanf(file, "%hd\n", num);

    //Go through commands
    while (!feof(file))
    {
        char command[5];
        int index;
        int replace;
        fscanf(file, "%s\t%d\t%d\n", command, &index, &replace);

        if (command[0] == 's') //set
        {
            //set(x, n, v) sets the nth bit of the number x to v
            *num ^= (-replace ^ *num) & (1 << index);
            printf("%d\n", *num);
        }
        else if (command[0] == 'c') //comp
        {
            //comp(x, n) sets the value of the nth bit of x to its complement (1 if 0 and 0 otherwise)
            *num ^= 1 << index;
            printf("%d\n", *num);
        }
        else if (command[0] == 'g') //get
        {
            //get(x, n) returns the value of the nth bit of the number x
            int bit = (*num >> index) & 1U;
            printf("%d\n", bit);
        }
        else
            break;
        
    }
    //Free pointer
    free(num);
}
