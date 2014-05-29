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
	int len = 1;
	temp = head;
	while ( temp != NULL )
	{
		len++;
		temp = temp->next;
	}
	if ( location <= len && location > 0)
	{
		int i;
		temp = head;
		for (i=0; i<location; i++)
		{
			targetNode = temp;
			temp = temp->next; //Any problems if temp = NULL?
		}
	}
	else
	{
		printf("%s\n", "The boundary error!" );
		targetNode = NULL;
	}
	free(temp);
	return targetNode;
}

/* Insert a node somewhere in the linked list */
void InsertNode( int data, int location)
{
	NODE *newNode, *left, *right;
	left = findNode(location-1);
	right = findNode(location);
	newNode = (NODE *) malloc(sizeof(NODE));
	newNode->data = data;
	newNode->next = right;
	if (left != NULL)
	{
		left->next = newNode;
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
    
    int data = 7;
	NODE *newNode, *left, *right;
	left = findNode(2);
	right = findNode(3);
	printf("the left is %d \n", left->data );
	printf("the right is %d \n", right->data );
	newNode = (NODE *) malloc(sizeof(NODE));
    if (left != NULL)
	{
		left->next = newNode;
	}
	newNode->data = data;
	newNode->next = right;
	printf("the left is %d \n", left->data );
	printf("the insert is %d \n", left->next->data );
	printf("the insert is %d \n", newNode->data );
	printf("the insert is %d \n", newNode->next->data );
    printf("the right is %d \n", right->data );

	/*
	int data, location;
	printf("Please enter a new node value:\n");
	scanf("%d", &data);
	printf("Please enter the location you want to add this value in:\n");
	scanf("%d", &location);
	InsertNode(data, location);
	DisplayList();
	*/
	return 0;
}