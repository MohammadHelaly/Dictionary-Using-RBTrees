#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node
{
    char data[50];
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

typedef struct BinarySearchTree
{
    Node* root;
} BinarySearchTree;

Node* createNode(char* str)
{
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->data,str);
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

int isEmpty(Node* root)
{
    return root == NULL;
}

BinarySearchTree createTree(char* filename)
{
    BinarySearchTree tree;
    tree.root=NULL;
    FILE* f=fopen(filename,"r");
    if (f==NULL)
    {
        printf("File not found. \n");
        return;
    }
    else if (ftell(f)!=0)
    {
        printf("File is empty. \n");
        fclose(f);
        return;
    }
    else
    {
        char* str=NULL;
        fseek(f,3,0);
        while(!feof(f))
        {
            str = (char*)malloc(50);
            fscanf(f,"%s",str);
            tree.root=insert(tree.root,str);
            free(str);
            str=NULL;
        }
        return tree;
    }
}

Node* insert(Node* root, char* str)
{
    if (root == NULL)
    {
        root = createNode(str);
        root->parent=root;
    }
    else if ((strcmp(str,root->data))<0)
    {
        root->left = insert(root->left, str);
        root->left->parent=root;
    }
    else if ((strcmp(str,root->data))>0)
    {
        root->right = insert(root->right, str);
        root->right->parent=root;
    }
    return root;
}

char* findMax(Node* root)
{
     if(root==NULL)
        return NULL;
    Node* temp = root;
     if(temp->right!=NULL)
        return FindMin(temp->right);
    return temp->data;
}

char* findMin(Node* root)
{
    if(root==NULL)
        return NULL;
    Node* temp = root;
    if(temp->left!=NULL)
        return FindMin(temp->left);
    return temp->data;
}

int max(int a, int b)
{
    return a>b?a:b;
}

int height(Node* root)
{
    if ( root == NULL)
        return -1;
    else
        return 1 + max(height(root->left),
        height(root->right));
}

int count(Node* root)
{
    if (root == NULL)
        return 0;
    else
           1 + count(root->left) + count(root->right);
}

Node* search(Node* root, char* str)
{
    if (isEmpty(root))
        return NULL;
    if (strcmp(str,root->data)==0)
        return root;
    else if (strcmp(str,root->data)<0)
    {
        if (root->left==NULL)
            return search(root->left, str);
    }
    else
    {
       if (root->right==NULL)
            return search(root->right, str);
    }
}

Node* inOrderSuccessor(Node* root, Node* temp)
{
    if( temp->right != NULL )
        return findMin(temp->right);
    Node* x = temp->parent;
    while(x != NULL && temp == x->right)
    {
        temp = x;
        x = x->parent;
    }
    return x;
}

Node* inOrderPredecessor(Node* root, Node* temp)
{
    if( temp->left != NULL )
        return findMax(temp->left);
    Node* x = temp->parent;
    while(x != NULL && temp == x->left)
    {
        temp = x;
        x = x->parent;
    }
    return x;
}

Node* clear(Node* root)
{
    if (!isEmpty(root))
    {
        clear(root->left);
        clear(root->right);
        free(root);
        root=NULL;
    }
    return root;
}

int main(int argc, char**argv)
{
    if(argc!=2)
    {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }
    char *str= (char*)malloc(100);
    printf("Enter a sentence : ");
    gets(str);
    BinarySearchTree tree = createTree(argv[1]);
    const char s[2] = " ";
    char *token;
    printf("Height of Tree = %d\n",height(tree.root));
    printf("Size of Tree = %d\n",size(tree.root));
    printf("Input Sentence : \"%s\"\n",str);
    token = strtok(str, s);
    printf("Output:\n");
    Node* temp;
    while( token != NULL )
    {
        temp = search(tree.root,token);
        if(strcmp(temp->data,token)==0)
            printf("\t.\t%s - CORRECT\n",token);
        else
        {
            printf("\t.%s - %s, %s, %s \n",token,temp->data
                   ,inOrderSuccessor(tree.root,temp)->data
                   ,(inOrderPredecessor(tree.root,temp)->data));
        }
        token = strtok(NULL, s);
    }
    tree.root = clear(tree.root);
    printf("\n%s",tree.root->data);
    free(str);
    str=NULL;
    return 0;
}


