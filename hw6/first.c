#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//char* hextobin(char* hex);
char* strnduplicate(char* n, int num);

int main(int argc, char* argv[])
{
    /*· L1 cache
        · The cache is write-through

        · When your program starts, all cache lines are empty (invalid).
        · The memory size is 2^48 bytes. Memory addresses are 48 bits 
            (zero extend the addresses in the trace file if they’re less than 48-bit in length).

        dont need to read or write to memory, just track when it does

        find out number of addesses that can be stored - sets?

        last column is the actual 48-bit memory address that is being accessed
        are we basically just comparing those memory address? do they need to be stored in the cache
        Placement in cache - Only placing to a cache if there is a miss
        2 types of replacement policy paths
        Hit - move the hit block to the back if LRU, no change if fifo
        Miss - add block to back and delete from front (shift left 1)
        LRU - least recently used - replace the block that was accessed least recently
        FIFO - first in first out - replace the block earliest added to the set 
        */

    // ./first <cache size> <associativity> <replace policy> <block size> <trace file>
    int cachesize = atoi(argv[1]);
    char* assoc = argv[2]; //direct, assoc, assoc:n
    char* policy = argv[3]; //lru or fifo
    int blocksize = atoi(argv[4]);

    //Error checks
    if (ceil(log2(cachesize)) != floor(log2(cachesize)) || ceil(log2(blocksize)) != floor(log2(blocksize)) || (strcmp("lru", policy) != 0 && strcmp("fifo", policy) != 0) )
    {
        printf("error");
        return 0;
    }

    int memreads = 0;
    int memwrites = 0;
    int hits = 0;
    int misses = 0;

    //Setting up the cache using command line params
    // · Need to figure out number of bits for the tag, set index, and block offset using the input
    // given: 48-bit architecture, cache size, block size
    // 1. find block size as 2^x > x = number of block index bits
    int blockbits = log((double)blocksize) / log(2.0);
    // 2. lines in cache = cache size / block size
    int lines = cachesize / blocksize;
    // 3. sets to hold those lines: lines / associativity of the cache (n-way) (n is lines per set)
    int sets = 0;
    int width = 0;
    if ( assoc[0] == 'd') //direct
        {sets = lines; width = 1;}
    else if ( assoc[5] == ':') //n-way
        {sets = lines / (assoc[6] - '0'); width = (assoc[6] - '0');}
    else //fully
        {sets = 1; width = lines;}
    // 4. find sets in terms of 2^x > x = set index bits
    int setbits = log(sets) / log(2);
    // 5. tag bits = 48 - set - block
    int tagbits = 48 - setbits - blockbits; //needs to be changed back to 48 eventually
    //creating cache
    char* cache[sets][width];

    //printf("%d, %d, %d, %dx%d\n", tagbits, setbits, blockbits, sets, width); 

    //fill cache with -1
    for (int i = 0; i < sets; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cache[i][j] = "-1";
            // printf("%s ",cache[i][j]);
        }
        // printf("\n");
    }
    // printf("%s ",cache[0][0]);

    //Going through file line by line
    FILE * trace = fopen (argv[5], "r");

    char line[60];
    char* tag;
    char* set;
    char* block;
    
    int filelen = 0;
    while (fgets(line, sizeof(line), trace) && ( (strncmp((line), "#eof", 4)) != 0))
        filelen++;

    char* ptrs[3*filelen];
    fclose(trace);
    trace = fopen (argv[5], "r");
        
    int linenum = 0;

    while (fgets(line, sizeof(line), trace) && ( (strncmp((line), "#eof", 4)) != 0)) 
    {
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') 
            line[--len] = '\0';
        char s[60];
        strcpy(s, line);
        char* token = strtok(s, " ");
        int count = 0;
        char command;
        char address[15];

        while (token) 
        {
            if (count == 1)
                command = token[0];
            if (count == 2)
                strcpy(address, token);
            count++;
            token = strtok(NULL, " ");
        }

        // How to find out if an address is in the cache:
        // 1. convert the address to binary
        char bin[50] = "";
        int i = 0;
        char hex[28];
        strcpy(hex, address+2);

        while (hex[i]) 
        {
            switch (hex[i]) 
            {
                case '0':
                    strcat(bin, "0000");
                    break;
                case '1':
                    strcat(bin, "0001");
                    break;
                case '2':
                    strcat(bin, "0010");
                    break;
                case '3':
                    strcat(bin, "0011");
                    break;
                case '4':
                    strcat(bin, "0100");
                    break;
                case '5':
                    strcat(bin, "0101");
                    break;
                case '6':
                    strcat(bin, "0110");
                    break;
                case '7':
                    strcat(bin, "0111");
                    break;
                case '8':
                    strcat(bin, "1000");
                    break;
                case '9':
                    strcat(bin, "1001");
                    break;
                case 'A':
                case 'a':
                    strcat(bin, "1010");
                    break;
                case 'B':
                case 'b':
                    strcat(bin, "1011");
                    break;
                case 'C':
                case 'c':
                    strcat(bin, "1100");
                    break;
                case 'D':
                case 'd':
                    strcat(bin, "1101");
                    break;
                case 'E':
                case 'e':
                    strcat(bin, "1110");
                    break;
                case 'F':
                case 'f':
                    strcat(bin, "1111");
                    break;
                default:
                    printf("\nInvalid hexadecimal digit %c",
                        hex[i]);
            }
            i++;
        }
        
        //Zero extend the addresses to reach 48 bits total
        while (strlen(bin) < 48)
        {
            char temp[50];
            strcpy(temp, bin);
            strcpy(bin+1, temp);
            bin[0] = '0';
        }
        
        // 2. splitting memory address into tag, set, block - in this order Address is tsb
        tag = strnduplicate(bin, tagbits); 
        set = strnduplicate(bin+tagbits, setbits); 
        block = strnduplicate(bin+tagbits+setbits, blockbits); 

        ptrs[linenum*3] = tag;
        ptrs[linenum*3 + 1] = set;
        ptrs[linenum*3 + 2] = block;
        
        //Binary to Decimal
         int binset = atoi(set);
        int decset =  0;
        for (int i = 0; binset; i++, binset /=10)
            if (binset % 10)
                decset += pow(2,i);
        //printf("%s, %d\n", set, decset); 

        // 3. Check cache for address (go to set row and then go through lines columns and match)
        int j = 0;
        int miss = 1;
        // Writes and reads - You do not need to simulate the memory itself in this assignment
        
        while (j < width)// && ((strcmp(cache[decset][j], "-1") != 0))) //moving through tags in a set
        {
            //printf("%s = \n%s\n", cache[decset][j], tag );

            if (strcmp(cache[decset][j], tag) == 0) //hit
            {
                hits++;
                --miss;
                if (command == 'W')
                    memwrites++; //Write through (write immediately to memory)
                // Nothing in memory gets incremented on a cache read hit
                if (strcmp(policy, "lru") == 0) //move hit block to the back 
                {
                    //Cases where it's the only thing in the set, only2 in the set, the width of the set is 2 or 1
                    if (width == 1 || j==width-1) // already the last block
                        break;
                    else
                    {
                        int i = j+1;
                        char* temp = cache[decset][j];
                        int var = 0;
                        while( i < width && (strcmp(cache[decset][i], "-1") != 0))
                        {
                            cache[decset][i-1] = cache[decset][i];
                            i++;
                            var = 1;
                        }
                        if (var)
                            cache[decset][i-1] = temp;
                    }
                }
                break;
            }
            j++;
        }
        if (miss)
        {
            misses++;
            if (command == 'W') // In write miss, assume that first one memory read then a memory write
                memwrites++;
            memreads++; // For read, just do memread
            //Placement in cache in the back
            int k = 0;
            // printf("%s", cache[decset][j]); // here
            while (k<width && strcmp(cache[decset][k], "-1") != 0) //until it reaches an empty location
            {
                k++;
            }
            if (k == width) //cache is full - replacement: shift everything over 1 starting from index 1; last one is new block
            {
                int i = 1;
                while (i < width)
                {
                    cache[decset][i-1] = cache[decset][i];
                    i++;
                }
                cache[decset][i-1] = tag;
            }
            else
                cache[decset][k] = tag;
        }
        linenum++;
    }
    linenum*=3;
    while(linenum > 0)
    {
        free(ptrs[linenum-1]);
        linenum--;
    }
    fclose(trace);
    printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", memreads, memwrites, hits, misses);
    return 0;
}
char* strnduplicate(char* n, int num)
{
    char *str;
    char *p;
    int i = 0;
    str = malloc(num + 1);
    p = str;
    while (i<num)
        {*p++ = *n++; i++;}
    *p = '\0';
    return str;
}
