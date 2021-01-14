#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int num;
    int count;
    struct node *next;
} node;

int main(int argc, char* argv[])
{
  FILE* file = fopen(argv[1], "r");
  node* front = NULL;

  if(file == NULL)
  {
      printf("error");
      exit(0);
  }

  //Scan contents from txt file into linked list 
  while (1)
  {
    char command = 'a';
    int value;
    int n = fscanf(file, "%c\t%d\n", &command, &value);
    if (n != 2)
        break;
    //printf("%c\t%d\n", command, value);
    if (command == 'i') //Then we are inserting a number
    {
      //Create node
      node* newNode; // declare a node
      newNode = (node*)malloc(sizeof(node));
      newNode -> num = value;
      newNode -> count = 1;
      newNode -> next = NULL;

      //Find insertion point
      node* ptr = front;
      //If list is empty
      if (front == NULL)
      {
        front = newNode;
      }
      //Parsing through the linked list to find proper insertion point
      else
      {
        while (ptr != NULL) 
        {
            //Duplicates
            if (ptr -> num == value)
            {
                ptr -> count = ptr->count+1;
                ptr = NULL;
                free(newNode);
            }
            //Adding to front 
            else if (front->num > value)
            {
                newNode -> next = front;
                front = newNode;
                ptr = NULL;

            }
            //Adding to end
            else if (ptr->next == NULL)
            {
                ptr->next = newNode;
                ptr = ptr->next;
                ptr = NULL;
            }
            //Adding between smaller # (ptr here) and larger #
            else if (ptr->num < value && ptr->next->num > value)
            {
                node* temp = ptr->next;
                ptr->next = newNode;
                newNode->next = temp;
                ptr = NULL;
                //free(temp);
            }
            else
            {
                ptr = ptr->next;
            }
        }
      }
    }
    else if (command == 'd') //Then deleting a number
    {
        node* ptr = front;
        while (ptr != NULL)
        {
            //Deleting from front 
            if (front->num == value)
            {
                //duplicates
                if (ptr->count > 1)
                    ptr -> count = ptr->count-1;

                //deleting actual entry
                else
                {
                    node* delete = front;
                    front = ptr->next;
                    free(delete);
                }
                ptr = NULL;
            }
            //Deleting next item
            else if (ptr->next != NULL && ptr->next->num == value)
            {
                //duplicates
                if (ptr->next->count > 1)
                    ptr->next->count = ptr->next->count-1;

                //deleting actual entry
                else
                {
                    node* delete = ptr->next;
                    ptr->next = ptr->next->next;
                    free(delete);
                    
                }
                ptr = NULL;
            }
            else
                ptr = ptr->next;
        }
    }

  }
  fclose(file);
  //First line: total nodes: go through all nodes and add up the count property
  int sum = 0;
  node* ptr = front;
  while (ptr != NULL)
  {
    sum += ptr->count;
    ptr = ptr->next;
  }
  printf("%d\n", sum);

  //Second line: Unique nodes: go through all nodes and print the value property followed by tab
  ptr = front;
  while (ptr != NULL)
  {
    printf("%d\t", ptr->num);
    ptr = ptr->next;
  }

  //Free LinkedList
  if (front == NULL)
    free(front);
  while(front!=NULL)
  {
    ptr = front;
    front = front->next;
    free(ptr);
  }
}
