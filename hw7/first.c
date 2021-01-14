#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(int argc, char* argv[])
{
/*
notes:
- going through the input commands for each combo of input vars
- output lines = 2^input vars
- ouput: 0 - 2^input vars -1 in order, last column is output
- first input is column 1, second column 2, etc.
- inefficient way to deal with temps - can only be as many as 2^input vars
*/
    //Command Line
    FILE* file = fopen (argv[1], "r");
    char line[60];
    int linect = 1;
    int numinputs = 0;
    int numoutputs = 0;
    int numtemps = 0;
    int inputindex = 0;
    int outputindex = 0;
    int filelen = 0;

    while (fgets(line, sizeof(line), file))
        filelen++;
    
    fclose(file);
    file = fopen (argv[1], "r");
    // printf("%d", filelen);

    //varnames array - use this index when trying to do operaitons
    char* *inputvars;
    char* *outputvars;
    char* *tempvars = malloc(sizeof(char*)*filelen); // 10 for var length
    for (int i = 0; i < filelen; i++)
        tempvars[i] = malloc((10) * sizeof(char));
    
    // - size of this? lenght and width of the 2d array?

    //Lines 1+2 of File
    while (linect<=2 && fgets(line, sizeof(line), file)) 
    {
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') 
            line[--len] = '\0';
        char s[60];
        strcpy(s, line);
        char* token = strtok(s, " ");
        int count = 1;

        while (token) //filling output vars and inputvars arrays
        {
            if (count == 2)
            {
                if (linect == 1)
                {
                    numinputs = atoi(token);
                    inputvars  = malloc(sizeof(char*)*numinputs); // 10 for var length
                    for (int i = 0; i < numinputs; i++)
                        inputvars[i] = malloc((10) * sizeof(char));

                }
                else if (linect == 2)
                {
                    numoutputs = atoi(token);
                    outputvars  = malloc(sizeof(char*)*numoutputs); // 10 for var length
                    for (int i = 0; i < numoutputs; i++)
                        outputvars[i] = malloc((10) * sizeof(char));
                    //outputvars  = (char*)malloc(sizeof(char*)*numoutputs*10); // 10 for var length
                }
            }
            else if (count >= 3)
            {
                if (linect == 1)
                {
                    strcpy(inputvars[inputindex], token);
                    inputindex++;
                }
                else if (linect == 2)
                {
                    strcpy(outputvars[outputindex], token);
                    outputindex++;
                }
            }
            count++;
            token = strtok(NULL, " ");
        }
        linect++;
    }
    //Print Check  
    // for (int i=0; i<inputindex; i++)
    //     printf("%s\n", inputvars[i]);
    // printf("\n");

    //Create truth table
    int** tt = malloc((int)pow(2, inputindex) * sizeof(int*));
    for (int i = 0; i < (int)pow(2, inputindex); i++) // # rows is pow(2, inputindex)
        tt[i] = malloc((inputindex+outputindex) * sizeof(int)); // # cols is inputindex + outputindex

    //Create temp variables tables - potentially linked list? - 
    //do a similar thing with these temp vars as the tempvars array names 
    //Max temporary variables is #commands -1 or file length - 2
    int** temps = malloc((int)pow(2, inputindex) * sizeof(int*));
    for (int i = 0; i < (int)pow(2, inputindex); i++) // # rows is pow(2, inputindex)
        temps[i] = malloc((filelen) * sizeof(int)); // # cols is filelen

    //Fill truth table with 0 to 2^inputindex - 1     
    for (int num = 0; num < (int)pow(2, inputindex); num++)
    {
        // int n =3;
        int n = num;
        int bin[32]; 
        // Fill binary rep with 0
        for (int j = 0; j < 32; j++)
            bin[j] = 0;
        int i=0; 
        for(i=0;n>0;i++)    
        {    
            bin[31-i]=n%2; //-32 
            n=n/2;    
        } 
        //starting from index 31 moving backwards until inputindex
        for (int i = inputindex-1; i >= 0; i--)
            tt[num][i] = bin[32-inputindex+i];
    }

/*
Essentially going through each of the lines of the commands for each of lines of input
maybe set up a for loop to do each line's command on each row
- only want to go through all the lines of the file once
*/

    //Rest of file - commands
    while (fgets(line, sizeof(line), file)) 
    {
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') 
            line[--len] = '\0';
        char s[60];
        strcpy(s, line);
        char* token = strtok(s, " ");
        int count = 1;
        char command[5];
        char arg1[10];
        char arg2[10];
        char out[10]; // output

        //Set up what variables the tokens are
        while (token) 
        {
            if (count == 1)
                strcpy(command, token);
            if (count == 2)
                strcpy(arg1, token);
            if (count == 3)
                strcpy(arg2, token);
            if (count == 4)
                strcpy(out, token);
            count++;
            token = strtok(NULL, " ");
        }

        //Assign Column indices + figure out if its temp or input
        int col1 = -1;
        int col2 = -1;
        for (int i = 0; i < inputindex; i++)
        {
            if( (strcmp(arg1, inputvars[i]) == 0) )
                col1 = i;
            if( (strcmp(arg2, inputvars[i]) == 0) )
                col2 = i;
        }
        int tempcol1 = -1;
        int tempcol2 = -1;
        for (int i = 0; i < numtemps; i++)
        {
            if( (strcmp(arg1, tempvars[i]) == 0) )
                tempcol1 = i;
            if( (strcmp(arg2, tempvars[i]) == 0) )
                tempcol2 = i;
        }
        //run for loop for each row of the truth table
        for (int i = 0; i < (int)pow(2, inputindex); i++)
        {
            int value = -1;
            int dig1 = -1;
            int dig2 = -1;
            if (col1 == -1)
                dig1 = temps[i][tempcol1];
            else
                dig1 = tt[i][col1];
            if (col2 == -1 && (strcmp(command, "NOT") != 0))
                dig2 = temps[i][tempcol2];
            else if (strcmp(command, "NOT") != 0)
                dig2 = tt[i][col2];
            if (strcmp(command, "NOT") == 0)
            {
                value = !(dig1);
                strcpy(out, arg2);
            }
            else if (strcmp(command, "AND") == 0)
                value = (dig1)&(dig2);
            else if (strcmp(command, "OR") == 0)
                value = (dig1)|(dig2);
            else if (strcmp(command, "NAND") == 0)
                value = !((dig1)&(dig2));
            else if (strcmp(command, "NOR") == 0)
                value = !((dig1)|(dig2));
            else if (strcmp(command, "XOR") == 0)
                value = (dig1)^(dig2);
            //finding target output - is it a temp variable or is it an output variable?
            //place in the output row, the and of both
            //Need to find out what variable to store this number in
            //Search for "out" in outputvars, then tempvars then insert
            int checktemps = 1;
            for (int j = 0; j < outputindex; j++)
            {
                if( (strcmp(out, outputvars[j]) == 0) )
                {
                    tt[i][inputindex+j]= value;
                    checktemps = 0;
                }
            }
            int inserttemp = 1;
            if (checktemps)
            { 
                for (int j = 0; j < numtemps; j++)
                {
                    if( (strcmp(out, tempvars[j]) == 0) )
                    {
                        temps[i][j] = value;
                        inserttemp = 0;
                    }
                }
            }
            if (inserttemp && checktemps)
            {
                strcpy(tempvars[numtemps], out);
                temps[i][numtemps] = value;
                numtemps++;
            }

        }    
    }
    //Output - print truth table
    for (int i=0; i<(int)pow(2, inputindex); i++)
    {
        for (int j=0; j< inputindex + outputindex; j++)
            printf("%d ", tt[i][j]);
        printf("\n");
    }
    //Free Input Vars
    for (int i = 0; i < inputindex; i++)
        free(inputvars[i]);
    free(inputvars);

    //Free Output Vars
    for (int i = 0; i < outputindex; i++)
        free(outputvars[i]);
    free(outputvars);

    //Free Temp Vars
    for (int i = 0; i < filelen; i++)
        free(tempvars[i]);
    free(tempvars);

    //Free Temps Table
    for (int i = 0; i < pow(2, inputindex); i++)
        free(temps[i]);
    free(temps);

    //Free Truth Table
    for (int i = 0; i < pow(2, inputindex); i++)
        free(tt[i]);
    free(tt);
}