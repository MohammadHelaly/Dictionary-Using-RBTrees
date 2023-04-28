#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node* root = NULL;
int count=0;
typedef struct
{
    char string[30];

}string;

struct node
{
    char* data;
    int color;
    struct node *left;
    struct node *right;
    struct node *parent;
};
struct node*createnode(char word[]){
        struct node* temp= (struct node*)malloc(sizeof(struct node));
        temp->right = NULL;
        temp->left = NULL;
        temp->parent = NULL;
        temp->data = word;
        temp->color = 1; ///red
}


void rightrotate(struct node* temp)
{
    struct node* left = temp->left;
    temp->left = left->right;
    if (temp->left)
        temp->left->parent = temp;
    left->parent = temp->parent;
    if (!temp->parent)
        root = left;
    else if (temp == temp->parent->left)
        temp->parent->left = left;
    else
        temp->parent->right = left;
    left->right = temp;
    temp->parent = left;
}

// Function performing left rotation
// of the passed node
void leftrotate(struct node* temp)
{
    struct node* right = temp->right;
    temp->right = right->left;
    if (temp->right)
        temp->right->parent = temp;
    right->parent = temp->parent;
    if (!temp->parent)
        root = right;
    else if (temp == temp->parent->left)
        temp->parent->left = right;
    else
        temp->parent->right = right;
    right->left = temp;
    temp->parent = right;
}



struct node* bst(struct node* root,struct node* temp)
{

    if (root == NULL)
        return temp;

    if ( strcmp(temp->data , root->data)<0 )
    {
        root->left = bst(root->left, temp);
        root->left->parent = root;
    }
    else if ( strcmp(temp->data ,root->data) >0 )
    {
        root->right = bst(root->right, temp);
        root->right->parent = root;
    }

    return root;
}
void fix(struct node* root, struct node* temp)
{
    struct node* parent = NULL;
    struct node* grand_parent = NULL;
     while ( (temp != root) && (temp->color != 0) && (temp->parent->color == 1))
    {
        parent = temp->parent;
        grand_parent = temp->parent->parent;
        if (parent == grand_parent->left)
        {

            struct node* uncle = grand_parent->right;

            /* Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if (uncle != NULL && uncle->color == 1)
            {
                grand_parent->color = 1;
                parent->color = 0;
                uncle->color = 0;
                temp=grand_parent;
            }

            else {

                /* Case : 2
                     pt is right child of its parent
                     Left-rotation required */
                if (temp == parent->right) {
                    leftrotate(parent);
                    temp = parent;
                    parent = temp->parent;
                }

                /* Case : 3
                     pt is left child of its parent
                     Right-rotation required */
                rightrotate(grand_parent);
                int tempp = parent->color;
                parent->color = grand_parent->color;
                grand_parent->color = tempp;
                temp = parent;
            }
        }

        else {
            struct node* uncle2 = grand_parent->left;

            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((uncle2 != NULL) && (uncle2->color == 1))
            {
                grand_parent->color = 1;
                parent->color = 0;
                uncle2->color = 0;
                temp = grand_parent;
            }
            else {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (temp == parent->left) {
                    rightrotate(parent);
                    temp = parent;
                    parent = temp->parent;
                }

                /* Case : 3
                     pt is right child of its parent
                     Left-rotation required */
                leftrotate(grand_parent);
                int x = parent->color;
                parent->color = grand_parent->color;
                grand_parent->color = x;
                temp = parent;
            }
        }




     }
     root->color=0;
}
void print(struct node *root){
if(root){
    print(root->left);
    printf("%s\n",root->data);
    print(root->right);

}
}

 void load(char x[]){



struct node *temp=createnode(x);

    root=bst(root,temp);
    fix(root,temp);

}
int search(struct node *root,char *word){
if(root==NULL){
    return 0;
}
if(strcmp(root->data,word)==0){
    return 1;
}


if(strcmp(root->data,word)>0){
   return search(root->left,word);
}
if(strcmp(root->data,word)<0){
   return search(root->right,word);

}

}

int size(struct node *root){
    return (root == NULL) ? 0 :
           1 + size(root->left) + size(root->right);
}

int maxHeight(int a, int b){
    return (a>=b) ? a : b;
}

int height(struct node *root){
    return (root == NULL) ? -1 :
           1 + maxHeight(height(root->left), height(root->right));
}

int main()
{
FILE *fp=fopen("EN-US-Dictionary.txt","r");
int count=0;

char x[48731][20];
int i=0;
while(i<48731){
    fscanf(fp,"%s\n",x[i]);
    i++;
}
i=0;
while(i<48731){
load(x[i]);
i++;
}

i=0;

char y[48731][20];
i=0;
while(i<48731){
    fscanf(fp,"%s\n",y[i]);
    i++;
}
i=0;
while(i<48731){
load(y[i]);
i++;
}
        printf("Dictionary loaded successfully into RedBlackTree.\n");
        printf("Size:%d\n",size(root));
        printf("Height:%d\n",height(root));
int t=1;
char word[20];
while(t){
    printf("\nEnter 0 to leave,1 to print all values,2 to insert a word,3 to search for word,4 to check size and height.\n");
    scanf("%d",&t);
    if(!t){
        break;
    }
    else if(t==1){
        print(root);
        printf("Size:%d\n",size(root));
        printf("Height:%d\n",height(root));
    }
    else if(t==2){
        printf("\nEnter word:\n");
        scanf("%s",word);
        if(!search(root,word)){
        load(word);
        printf("Word successfully inserted.\n");
        printf("Size:%d\n",size(root));
        printf("Height:%d\n",height(root));
    }
    else{
        printf("Word already in dictionary.\n");
    }

    }
    else if(t==3){
       printf("\nEnter word:\n");
       scanf("%s",word);
       if (search(root,word)== NULL)
        printf("Word not in dictionary.");
       else
         printf("Word found in dictionary: %s",word);
    }
    else if(t==4){
        printf("Size:%d\n",size(root));
        printf("Height:%d\n",height(root));
    }
    else{
        printf("Please select a valid number.");
}
}
    return 0;
}
