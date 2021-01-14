#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  int input[21];
  int even[20];
  int odd[20];
  
  int index = 0;
  FILE* file = fopen(argv[1], "r");

  //Scan contents from txt file into array 
  while (1)
  {
    int x;
    int n = fscanf(file, "%d\t", &x);
    if (n != 1)
      break;
    input[index]=x;
    index++;  
  }

  //Split input array into even and odd arrays
  int e = 0;
  int o = 0;
  for (int i=1; i<index; i++)
  {
    if (input[i]%2 == 0)
    {
      even[e] = input[i];
      e++;
    }
    else
    {
      odd[o] = input[i];
      o++;
    }
  }

  //printf("\n");

  //e and o contain the number of even and odd numbers
  //sorting even numbers ascending
  for (int i = 0; i < e; i++)
  {
    for (int j = i+1; j < e; j++)
    {
      if (even[j] < even[i])
      {
        int temp = even[i];
        even[i] = even[j];
        even[j] = temp;
      }
    }
    printf("%d\t", even[i]);
  }

  //sorting odd numbers descending
  for (int i = 0; i < o; i++)
  {
    for (int j = i+1; j < o; j++)
    {
      if (odd[j] > odd[i])
      {
        int temp = odd[i];
        odd[i] = odd[j];
        odd[j] = temp;
      }
    }
    printf("%d\t", odd[i]);
  }
  //printf("\n");
}