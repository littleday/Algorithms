#include <stdio.h> 
#include <stdlib.h>
struct node{
    int key;
    struct node *left_p, *right_p;
};

struct node *creatNode(int key)
{
    struct node*newNode_p = (struct node*)malloc(sizeof(struct node));
    newNode_p->key = key;
    newNode_p->left_p = NULL;
    newNode_p->right_p = NULL;
    return newNode_p;
};

// Insert 
void insert(struct node **tree_pp, struct node *newNode_p)
{
    if ((tree_pp) == NULL)
    {
        return;   
    }
    else
    {
        if ((*tree_pp) == NULL)
        {
            (*tree_pp) = newNode_p;
        }
        else
        {
            if (newNode_p->key < (*tree_pp)->key)
            {
                insert(&(*tree_pp)->left_p, newNode_p);
            }
            else
            {
                if (newNode_p->key > (*tree_pp)->key)
                {
                    insert(&(*tree_pp)->right_p, newNode_p);
                }
            }
        }
    }
}
//search
int search(struct node **tree_pp, int key)
{
    if ((tree_pp) == NULL)
    {
        return -1;
    }
    if ((*tree_pp) == NULL)
    {
        return 0;
    }
    else
    {
        if ((*tree_pp)->key < key)
        {
            return search(&(*tree_pp)->right_p, key);
        }
        if ((*tree_pp)->key > key)
        {
            return search(&(*tree_pp)->left_p, key);
        }
        if ((*tree_pp)->key == key)
        {
            return 1;
        }
        return 0;

    }
}
// Delete
// Print the tree
void printTree(struct node** tree_pp){
    if ((tree_pp) != NULL)
    {
        printf("Current node is %d\n", (*tree_pp)->key);
        if ((*tree_pp)->left_p != NULL)
        {
            printf("The left node is %d\n", (*tree_pp)->left_p->key);
            printTree(&(*tree_pp)->left_p);
        }
        if ((*tree_pp)->right_p != NULL)
        {
            printf("The right node is %d\n", (*tree_pp)->right_p->key);
            printTree(&(*tree_pp)->right_p);
        }
    }
}

int main(int argc, char const *argv[])
{
    struct node *tree_p = NULL;
    struct node *newNode_p = NULL;
    int nodes[10] ={5,4,6,2,1,3,9,7,8,10};
    int i;
    for (i = 0; i < 10; ++i)
    {
        newNode_p = creatNode(nodes[i]);
        insert(&tree_p, newNode_p);
    }
    printTree(&tree_p);
    if (search(&tree_p, 12) == 1)
    {
        printf("Find it\n");
    }
    else
        printf("Do not find\n");
    return 0;
}