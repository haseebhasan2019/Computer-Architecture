#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
} node;

node* insert(node* root, node* newNode)
{
    if (root==NULL)
        return newNode;
    if (root->val > newNode->val)
        root->left = insert(root->left, newNode);
    else if (root->val < newNode->val)
        root->right = insert(root->right, newNode);
    else
        free(newNode);
    return root;
}

void traverse(node* root)
{
  if(root!=NULL)
  {
    traverse(root->left);
    printf("%d\t", root->val);
    traverse(root->right);
  }
}

void freeTree(node* root)
{
  if (root!=NULL)
  {
      freeTree(root->left);
      freeTree(root->right);
      free(root);
  }
}  

int main(int argc, char* argv[])
{

    FILE* file = fopen(argv[1],"r");
    if (file == NULL)
    {
      printf("error");
      exit(0);
    }
    else
    {
        int data;
        char command;
        node* root = NULL;
        while(!feof(file))
        {
            fscanf(file,"%c\t%d\n",&command,&data);
            if (command=='i')
            {
                //create node
                node* newNode = (struct node*)malloc(sizeof(struct node));
                newNode->val = data;
                newNode->left = NULL;
                newNode->right = NULL;

                //insert
                root = insert(root,newNode);
            }

        }
        traverse(root);
        freeTree(root);
    }
    fclose(file);
  }

