/******
*Binary Search Tree Implementation
*Input: array from console
*
*
******/
#include <stdio.h> 
#include <stdlib.h>
struct node{
    int key;
    struct node *left_p, *right_p;
};
// Create a new node
struct node *creatNode(int key)
{
    struct node*newNode_p = (struct node*)malloc(sizeof(struct node));
    newNode_p->key = key;
    newNode_p->left_p = NULL;
    newNode_p->right_p = NULL;
    return newNode_p;
};

// Insert 
struct node* insert(struct node *tree_p, int key)
{
    if ((tree_p) == NULL)
    {
        return creatNode(key);   
    }
    else
    {
        if (key <= (tree_p)->key)
        {
            tree_p->left_p = insert(tree_p->left_p, key);
        }
        else
        {
            if (key > (tree_p)->key)
            {
                tree_p->right_p = insert((tree_p)->right_p, key);
            }
        }
        return tree_p;
    }
}

// Search
struct node* search(struct node *tree_p, int key)
{
    if ((tree_p) == NULL)
    {
        return NULL;
    }
    else
    {
        if ((tree_p)->key < key)
        {
            return search((tree_p)->right_p, key);
        }
        if ((tree_p)->key > key)
        {
            return search((tree_p)->left_p, key);
        }
        else
        {
            return (tree_p);
        }

    }
}

// Print the tree
void printTree(struct node* tree_p){
    if ((tree_p) != NULL)
    {
        printf("Current node is %d\n", (tree_p)->key);
        if (tree_p->left_p != NULL)
        {
            printf("The left node is %d\n", (tree_p)->left_p->key);
            printTree(tree_p->left_p);
        }
        if ((tree_p)->right_p != NULL)
        {
            printf("The right node is %d\n", (tree_p)->right_p->key);
            printTree((tree_p)->right_p);
        }
    }
}

// Build this binary search tree
struct node* buildTree(struct node* tree_p, int input[], int size)
{
    int mid = input[size/2 - 1];
    tree_p = insert(tree_p, mid);
    int i;
    for(i=0; i < size; i++)
    {
        if ( i != size/2 - 1)
        {
            tree_p = insert(tree_p, input[i]);
        }
    }
    return tree_p;
}
// Get the size of the tree (node number)
// Get the depth of the tree


int main(int argc, char const *argv[])
{
    int size;
    printf("Please enter the number of tree node you want to initial:\n");
    scanf("%d", &size);
    int input[size];
    printf("Please enter %d numbers, separated them by return: \n", size);
    int i;
    for (i = 0; i < size; ++i)
    {
        scanf("%d", &input[i]);
    }
    struct node *tree_p = NULL;
    tree_p = buildTree(tree_p, input, size);
    printTree(tree_p);
    if (search(tree_p, 5) != NULL)
    {
        printf("Find it\n");
    }
    else
        printf("Do not find\n");
    return 0;
}