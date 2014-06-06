#include <stdio.h>
#include <stdlib.h>
#define N 4
/* Define a node*/
typedef struct node{
	int data; //the type of data stored in the linked list
	struct node *next; //the pointer to the next
}NODE;

NODE * head = NULL;
NODE * currentNode = NULL;

/* Add a node */
void addNode( int data )
{
	NODE *newNode;
	newNode = (NODE *)malloc(sizeof(NODE)); //Why need malloc?
	newNode->data = data;
	newNode->next = NULL;
	if (head == NULL)
	{
		head = newNode;
		currentNode = newNode;
	}
	else
	{
		currentNode->next = newNode;
		currentNode = newNode; 
	}

}

NODE *findNode( int location )
{
	NODE *targetNode, *temp;
	if (location > 0)
	{
		int i;
		temp = head;
		for (i=0; i<location; i++)
		{
			targetNode = temp;
			if ( targetNode == NULL )
			{
				printf("%s\n", "Boundary is beyound!");
				break;
			}
			temp = temp->next; //Any problems if temp = NULL?
		}
	}
	else
	{
		printf("%s\n", "Please enter a positive location!" );
		targetNode = NULL;
	}
	//printf("pointer is %p\n", temp);
	return targetNode;
}

/* Insert a node somewhere in the linked list */
void InsertNode( int data, int location)
{
	NODE *newNode, *left, *right;
	left = findNode(location-1);
	right = findNode(location);
	if ( left!=NULL && right == NULL )
	{
		newNode = (NODE *) malloc(sizeof(NODE));
		newNode->data = data;
		newNode->next = NULL;
		left->next = newNode;
	}
	else
	{
		newNode = (NODE *) malloc(sizeof(NODE));
	    newNode->data = data;
	    newNode->next = right;
	    if (left != NULL)
	    {
		    left->next = newNode;
	    }
	}

}

void DeleteNode( int location )
{
	NODE *targetNode, *left;
	targetNode = findNode(location);
	if ( targetNode == NULL )
	{
		printf("%s\n", "No node in current position!");
	}
	if ( targetNode->next == NULL )
	{
		left = findNode(location-1);
		left->next = NULL;
	}
	else
	{
		left = findNode(location-1);
		left->next = targetNode->next;
	}
}

void DisplayList()
{
    NODE *temp;
	temp = head;
	while( temp!=NULL )
	{
		printf("%d", temp->data);
		temp = temp->next;
		if (temp !=NULL)
			printf("--->");
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
	printf("Please enter a list you want to add to the linked list %d : \n", N);
	int numbers[N];
	//numbers = (int *) malloc (N * sizeof(int));
	int i;
	for (i = 0; i < N; ++i)
	{
		scanf ("%d", &numbers[i]);
		addNode(numbers[i]);
	}
	DisplayList();
	
	int data, location;
	printf("Please enter a new node value:\n");
	scanf("%d", &data);
	printf("Please enter the location you want to add this value in:\n");
	scanf("%d", &location);
	InsertNode(data, location);
	DisplayList();
	DeleteNode(2);
	DisplayList();

	return 0;
}