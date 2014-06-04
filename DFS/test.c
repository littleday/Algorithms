#include <stdio.h> 
#include <stdlib.h>

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

int main(int argc, char const *argv[])
{
	int vertexs = 6;
	struct Graph*graph = createGraph(vertexs);
        addEdge(1,2,graph);
        addEdge(1,3,graph);
        addEdge(1,4,graph);
    int i;
    for (i = 0; i < vertexs; ++i)
    {
    	struct AdjNode* node = graph->vertexs[i].head;
    	printf("vertext: %d\n", i);
    	while(node)
    	{
    		printf("->%d\n", node->dest);
    		node = node->next;
    	}
    	printf("\n");
    }
	return 0;
}