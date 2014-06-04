#include <stdio.h> 
#include <stdlib.h>
#define N 6;
/* Adjacency list node */
struct AdjNode{
	int dest;
	struct AdjNode *next;
};

/* AdjList*/
struct AdjList{
	struct AdjNode * head;
};

struct Graph{
	int number;
	struct AdjList *vertexs;
};

/* Create graph */
struct Graph* createGraph( int number ){
	struct Graph *newGraph;
	newGraph = (struct Graph*)malloc(sizeof(struct Graph));
	newGraph->number = number;
	newGraph->vertexs = (struct AdjList*)malloc(number*sizeof(struct AdjList));
	int i;
	for (i = 0; i < number; ++i)
	{
		newGraph->vertexs[i].head = NULL;
	}
    return newGraph;
};

/* Add Node */
struct AdjNode* addNode (int dest)
{
	struct AdjNode *newNode;
	newNode = (struct AdjNode*)malloc(sizeof(newNode));
	newNode->dest = dest;
	newNode->next = NULL;
    return newNode;
};

/* Create eage */

void addEdge(int src, int dest, struct Graph* newGraph){
	struct AdjNode *newNode = addNode(dest);
	newNode->next = newGraph->vertexs[src].head;
	newGraph->vertexs[src].head = newNode;
	newNode = addNode(src);
	newNode->next = newGraph->vertexs[dest].head;
	newGraph->vertexs[dest].head = newNode;
}
/* Depth first search */
void dfsTraverse(struct Graph*graph, int vertex, int visited[]){
	int number = graph->number;
	visited[vertex] = 1;
	printf("Current vertex is: %d\n", vertex);
	int i;
	for (i = 0; i < number; ++i)
	{
		struct AdjNode * newNode = graph->vertexs[vertex].head;
		while (newNode != NULL)
		{
			if (newNode->dest ==  i && visited[i] == 0)
			{
				dfsTraverse(graph, i, visited);
			}
			newNode = newNode->next;
		}
	}
}

void dfs(struct Graph* graph, int visited[]){
	int i;
	int number = graph->number;
	for (i = 0; i < number; ++i)
	{
		if (visited[i] == 0)
		{
			dfsTraverse(graph, i, visited);
		}
	}

}

struct Queue{
	struct AdjNode *node;
	struct Queue *next;
};
struct Queue *front = NULL;
struct Queue *rear = NULL;

void enQueue(struct AdjNode *node)
{
	if (front == NULL)
	{
		front->node = node;
		front->next = NULL;
		rear = front;
	}
	else
	{
		struct Queue *newMember = (struct Queue*)malloc(sizeof(newMember));
		newMember->node = node;
		newMember->next =NULL;
		struct Queue *temp;
		temp = front;
		while (temp->next!= NULL)
		{
			temp = temp->next;
		}
		temp->next = newMember;
		rear = newMember;
	}
}

void deQueue()
{
	if (front->next == NULL)
	{
		front = NULL;
		rear = NULL;
	}
	else
	{
		front = front->next;
	}
}

/* BFS traverse */
void bfs(struct Graph*graph){
	int number = graph->number;
	int visited[number];
	//queue<int> q;
	int i;
	for (i = 0; i < number; ++i)
	{
		visited[i] = 0;
	}
	for (i = 0; i < number; ++i)
	{
		if ( visited[i] != 1 )
		{
			//visited[i] = 1;
			struct AdjNode *newNode = graph->vertexs[i].head;
			enQueue(newNode);
			//printf("Current vertex is: %d\n", i);
			while(front != NULL)
			{
				struct AdjNode *temp = front->node;
				while(temp->next != NULL)
				{
					temp = temp->next;
					if(visited[temp->dest] != 1)
					{
						enQueue(temp);
					}
				}
				visited[front->node->dest] = 1;
				printf("Current vertex is: %d\n", front->node->dest);
				deQueue();

			}
		}
	}

}

int main(int argc, char const *argv[])
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int node_1, node_2;
	fp = fopen("test.txt", "r");
	if ( fp == NULL )
		exit(1);
	int vertexs = N;
	struct Graph*graph = createGraph(vertexs);
	while ((read = getline(&line, &len, fp)) != -1) 
	{
		//printf("Retrieved line of length %zu :\n", read);
        //printf("%s", line);
        sscanf(line, "%d %d", &node_1, &node_2);
        printf("%d and %d\n", node_1, node_2);
        addEdge(node_1,node_2,graph);
    }
    int i;
    for (i = 0; i < vertexs; ++i)
    {
    	struct AdjNode* node = graph->vertexs[i].head;
    	printf("vertext: %d\n", i);
    	while(node != NULL)
    	{
    		printf("->%d\n", node->dest);
    		node = node->next;
    	}
    	printf("\n");
    }
    int visited[vertexs];
    int m;
    for (m = 0; m < vertexs; m++)
    {
    	visited[m] = 0;
    }
    dfs(graph, visited);
    bfs(graph);
    if(line)
    	free(line);
	return 0;
}