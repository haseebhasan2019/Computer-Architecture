#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
} node;

struct node* hashtable[10000]; //create hashtable

int main(int argc, char* argv[])
{

    FILE* file = fopen(argv[1],"r");
    if (file == NULL)
    {
      printf("error");
      exit(0);
    }

    int data;
    char command;
    int colcounter = 0;
    int scounter = 0;
    while(!feof(file))
    {
        fscanf(file,"%c\t%d\n",&command,&data);
        if(command == 'i')
        {
            //make node
            node* newNode = (struct node*)malloc(sizeof(struct node));
            newNode->val=data;
            newNode->next=NULL;
            
            //insert        
            int index = newNode->val%10000; 
            if(index<0) 
                index = index+10000;
            
            //add the first node
            if(hashtable[index]==NULL)
            {
                hashtable[index]=newNode;
            } 
            //collision
            else
            {
                node* ptr;
                int flag=0;
                ptr= hashtable[index];
                node* prev=NULL;
                while(ptr!= NULL)
                {
                    if(ptr-> val!=newNode->val)
                    {
                        prev=ptr;
                        ptr=ptr->next;
                    }
                    else
                    {
                        flag=1;
                        free(newNode);
                        break;
                    }
                }
                if(flag==0)
                {
                    prev->next=newNode;
                }
                colcounter++;
            }
        }

        if(command=='s')
        {
            //search
            node* ptr;
            int index;
            index = data%10000;
            if (index<0)
            {//if it's a negative number
                index=index+10000;
            }
            ptr=hashtable[index];
            while (ptr!=NULL)
            {
                if (ptr->val==data)
                {
                    scounter++;
                    break;
                }
                else
                {
                    ptr=ptr->next;}
                }
        }
    }
    printf("%d\n",colcounter);
    printf("%d",scounter);
    fclose(file);

    //free hashtable
    node* indexptr=NULL;
    for (int index=0; index<10000; index++)
    {
        indexptr=hashtable[index];
        while(indexptr!=NULL)
        {
            node* delete = indexptr;
            indexptr = indexptr->next;
            free(delete);
        }
    }
}