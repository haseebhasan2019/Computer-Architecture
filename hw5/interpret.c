#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    //Enter entire file into an array
    char line[100][25];
    int lines = 0; //number of lines in the file
    FILE *assembly = fopen (argv[1], "r");

    char temp[25];
    while(fgets(line[lines], 25, assembly))
    {
        strcpy(temp, line[lines]);
        line[lines][strlen(line[lines])-1] = '\0';
        lines++;
    }
    strcpy(line[lines-1], temp);
    int regs[4];
    int ptr = 0;

    //Loop through the array till the end index is reached
    while (ptr < lines)
    {
        int linenum;
        int intx;
        int inty;
        // Input/Output
        //Read
        if ( (strncmp((line[ptr]), "read", 4)) == 0)
        {
            int val;
            scanf("%i", &val);
            if ( (line[ptr][4+1] == 'a') )
                regs[0] = val;
            else if ( (line[ptr][4+1] == 'b') )
                regs[1] = val;
            else if ( (line[ptr][4+1] == 'c') )
                regs[2] = val;
            else if ( (line[ptr][4+1] == 'd') )
                regs[3] = val;
        }

        //Print
        if ( (strncmp((line[ptr]), "print", 5)) == 0)
        {
            if ( (line[ptr][5+1] == 'a') )
                printf("%i", regs[0]);
            else if ( (line[ptr][5+1] == 'b') )
                printf("%i", regs[1]);
            else if ( (line[ptr][5+1] == 'c') )
                printf("%i", regs[2]);
            else if ( (line[ptr][5+1] == 'd') )
                printf("%i", regs[3]);
            else //print the number
                for (int i = 6; i < strlen(line[ptr]) + 1; i++)
                    printf("%c", line[ptr][i]);
        }

        //Arithmetic
        //add
        if ( (strncmp((line[ptr]), "add", 3)) == 0)
        {
            int number = 0;
            int length = 2;
            if ( (line[ptr][3+1] == 'a') )
                number = regs[0]; 
            else if ( (line[ptr][3+1] == 'b') )
                number = regs[1];
            else if ( (line[ptr][3+1] == 'c') )
                number = regs[2];
            else if ( (line[ptr][3+1] == 'd') )
                number = regs[3];
            else //it's a number
            {
                char num[16]; //get the number as a string
                length = 0;
                for (int i = 4; i < strlen(line[ptr]); i++)
                {
                    num[i] = line[ptr][i];
                    length++;
                }
                number = atoi(num);                    
            }
            if ( (line[ptr][5+length] == 'a') )
                regs[0] += number;
            else if ( (line[ptr][5+length] == 'b') )
                regs[1] += number;
            else if ( (line[ptr][5+length] == 'c') )
                regs[2] += number;
            else if ( (line[ptr][5+length] == 'd') )
                regs[3] += number;
        }

        //sub
        if ( (strncmp((line[ptr]), "sub", 3)) == 0)
        {
            int number = 0;
            int length = 2;
            if ( (line[ptr][3+1] == 'a') )
                number = regs[0]; 
            else if ( (line[ptr][3+1] == 'b') )
                number = regs[1];
            else if ( (line[ptr][3+1] == 'c') )
                number = regs[2];
            else if ( (line[ptr][3+1] == 'd') )
                number = regs[3];
            else //it's a number
            {
                char num[16]; //get the number as a string
                length = 0;
                for (int i = 0; i < strlen(line[ptr]) - 7; i++)
                {
                    num[i] = line[ptr][i+4];
                    length++;
                }
                number = atoi(num);                    
            }
            if ( (line[ptr][5+length] == 'a') )
                regs[0] -= number;
            else if ( (line[ptr][5+length] == 'b') )
                regs[1] -= number;
            else if ( (line[ptr][5+length] == 'c') )
                regs[2] -= number;
            else if ( (line[ptr][5+length] == 'd') )
                regs[3] -= number;
        }

        //mul
        if ( (strncmp((line[ptr]), "mul", 3)) == 0)
        {
            int number = 0;
            int length = 2;
            if ( (line[ptr][3+1] == 'a') )
                number = regs[0]; 
            else if ( (line[ptr][3+1] == 'b') )
                number = regs[1];
            else if ( (line[ptr][3+1] == 'c') )
                number = regs[2];
            else if ( (line[ptr][3+1] == 'd') )
                number = regs[3];
            else //it's a number
            {
                char num[16]; //get the number as a string
                length = 0;
                for (int i = 0; i < strlen(line[ptr]) - 7; i++)
                {
                    num[i] = line[ptr][i+4];
                    length++;
                }
                number = atoi(num);                    
            }
            if ( (line[ptr][5+length] == 'a') )
                regs[0] *= number;
            else if ( (line[ptr][5+length] == 'b') )
                regs[1] *= number;
            else if ( (line[ptr][5+length] == 'c') )
                regs[2] *= number;
            else if ( (line[ptr][5+length] == 'd') )
                regs[3] *= number;
        }

        //div
        if ( (strncmp((line[ptr]), "div", 3)) == 0)
        {
            int number = 0;
            int length = 2;
            if ( (line[ptr][4] == 'a') )
                number = regs[0]; 
            else if ( (line[ptr][4] == 'b') )
                number = regs[1];
            else if ( (line[ptr][4] == 'c') )
                number = regs[2];
            else if ( (line[ptr][4] == 'd') )
                number = regs[3];
            else //it's a number
            {
                char num[16]; //get the number as a string
                length = 0;
                for (int i = 0; i < strlen(line[ptr]) - 7; i++)
                {
                    num[i] = line[ptr][i+4];
                    length++;
                }
                number = atoi(num);                    
            }
            if ( (line[ptr][5+length] == 'a') )
                regs[0] = regs[0] / number;
            else if ( (line[ptr][5+length] == 'b') )
                regs[1] = regs[1] / number;
            else if ( (line[ptr][5+length] == 'c') )
                regs[2] = regs[2] / number;
            else if ( (line[ptr][5+length] == 'd') )
                regs[3] = regs[3] / number;
        }

        //Moving data - copy
        if ( (strncmp((line[ptr]), "mov", 3)) == 0)
        {
            int number = 0;
            int length = 2;
            if ( (line[ptr][3+1] == 'a') )
                number = regs[0]; 
            else if ( (line[ptr][3+1] == 'b') )
                number = regs[1];
            else if ( (line[ptr][3+1] == 'c') )
                number = regs[2];
            else if ( (line[ptr][3+1] == 'd') )
                number = regs[3];
            else //it's a number
            {
                char num[16]; //get the number as a string
                length = 0;
                for (int i = 0; i < strlen(line[ptr]) - 7; i++)
                {
                    num[i] = line[ptr][i+4];
                    length++;
                }
                number = atoi(num);                    
            }
            if ( (line[ptr][5+length] == 'a') )
                regs[0] = number;
            else if ( (line[ptr][5+length] == 'b') )
                regs[1] = number;
            else if ( (line[ptr][5+length] == 'c') )
                regs[2] = number;
            else if ( (line[ptr][5+length] == 'd') )
                regs[3] = number;
        }
        
        //Jumps 
        if ( (strncmp((line[ptr]), "j", 1)) == 0)
        {
            //Tokenize the entire line in one runthrough
            char s[20];
            strcpy(s, line[ptr]);
            char* token = strtok(s, " ");
            int count = 0;

            char input[3];
            char x[16];
            char y[16];

            while (token) 
            {
                //printf("token: %s\n", token);
                if (count == 1)
                {
                    for (int i = 0; i < strlen(token); i++)
                        input[i] = token[i];
                    linenum = atoi(input);
                }
                if (count == 2)
                {
                    if ( (token[0] == 'a') )
                        intx = regs[0];
                    else if ( (token[0] == 'b') )
                        intx = regs[1]; 
                    else if ( (token[0] == 'c') )
                        intx = regs[2];
                    else if ( (token[0] == 'd') )
                        intx = regs[3];
                    else //it's a number
                    {
                        for (int i = 0; i < strlen(token); i++)
                            x[i] = token[i];
                        intx = atoi(x);
                    }
                }
                if (count == 3)
                {
                    if ( (token[0] == 'a') )
                        inty = regs[0];
                    else if ( (token[0] == 'b') )
                        inty = regs[1]; 
                    else if ( (token[0] == 'c') )
                        inty = regs[2];
                    else if ( (token[0] == 'd') )
                        inty = regs[3];
                    else //it's a number
                    {
                        for (int i = 0; i < strlen(token); i++)
                            y[i] = token[i];
                        inty = atoi(y);
                    }
                }
                count++;
                token = strtok(NULL, " ");
            }
        }
        if ( (strncmp((line[ptr]), "jmp", 3)) == 0)
            ptr = linenum-1;
        if ( (strncmp((line[ptr]), "je", 2)) == 0)
            if (intx == inty)
                ptr = linenum-1;
        if ( (strncmp((line[ptr]), "jne", 3)) == 0)
            if (intx != inty)
                ptr = linenum-1;
        if ( (strncmp((line[ptr]), "jge", 3)) == 0)
            if (intx >= inty)
                ptr = linenum-1;
        else if ( (strncmp((line[ptr]), "jg", 2)) == 0)
            if (intx > inty)
                ptr = linenum-1;
        if ( (strncmp((line[ptr]), "jle", 3)) == 0)
            if (intx <= inty)
                ptr = linenum-1;
        else if ( (strncmp((line[ptr]), "jl", 2)) == 0)
            if (intx < inty)
                ptr = linenum-1;
        
	    ptr++;
    }
}