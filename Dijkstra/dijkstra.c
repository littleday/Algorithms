#include <stdio.h> 
#include <stdlib.h>
#define N 6;
/* Adjacency list node */
struct AdjNode{
	int id;
	int weight;
	struct AdjNode *next;
};

/* AdjList*/
struct AdjList{
	struct AdjNode *head;
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
		struct AdjNode *vertexNode = (struct AdjNode*)malloc(sizeof(struct AdjNode));
		vertexNode->id = i + 1;
		vertexNode->weight = 0;
		vertexNode->next = NULL;
		newGraph->vertexs[i].head = vertexNode;
	}
    return newGraph;
};

/* Add Node */
struct AdjNode* addNode (int id, int weight)
{
	struct AdjNode *newNode;
	newNode = (struct AdjNode*)malloc(sizeof(newNode));
	newNode->id = id;
	newNode->weight = weight;
	newNode->next = NULL;
    return newNode;
};

/* Create eage and weight for eage */

void addEdge(int src, int dest, int weight, struct Graph* newGraph){
	struct AdjNode *newNode = addNode(dest,weight);
	struct AdjNode *temp;
	temp = newGraph->vertexs[src-1].head;
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newNode;
	// undirected graph
	newNode = addNode(src,weight);
	temp = newGraph->vertexs[dest-1].head;
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newNode;
}

/* Dijkstra --find the miniest path from A to B */
void dijkstra(struct Graph*graph, int src, int dest){
	int number = graph->number;
	int solved[number];
	int i;
	for (i = 0; i < number; ++i)
	{
		solved[i] = 0;
	}
	solved[src-1] = 1;
	while (solved[dest-1] != 1)
	{
		int records[number][number], count;
		int j,k;
		for (j = 0; j < number; ++j)
			for (k = 0; k < number; k++)
			{
				records[j][k] = 0;
			}
		count = 0;
		for (i = 0; i < number; ++i)
		{
			if (solved[i] == 1)
			{
				struct AdjNode *v = graph->vertexs[i].head;
				struct AdjNode *temp = v;
				while (temp->next != NULL)
				{
					temp = temp->next;
					if (solved[temp->id-1] != 1)
					{
						records[v->id-1][temp->id-1] = temp->weight;
						count++;
					}
				}

			}
		}
		if (count == 0)
		{
			printf("Cannot find a path from %d to %d \n", src, dest);
			break;
		}
		else
		{
			int x,y,tsrc, tdest, tpath;
			tsrc = 0;
			tdest = 0; 
			tpath = 1000000; // unlimited max set
			for (x = 0; x < number; ++x)
				for (y = 0; y < number; ++y)
				{
					if (records[x][y] != 0)
					{
						if (records[x][y] <= tpath)
						{
							tsrc = x+1;
							tdest = y+1;
							tpath = records[x][y];
						}
					}	
				}
			printf("Next path is from %d to %d with length %d \n", tsrc, tdest, tpath);
			solved[tdest - 1] = 1;
		}

	}
}
int main(int argc, char const *argv[])
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int node_1, node_2, weight;
	fp = fopen("test.txt", "r");
	if ( fp == NULL )
		exit(1);
	int vertexs = N;
	struct Graph*graph = createGraph(vertexs);
	while ((read = getline(&line, &len, fp)) != -1) 
	{
		//printf("Retrieved line of length %zu :\n", read);
        //printf("%s", line);
        sscanf(line, "%d %d %d", &node_1, &node_2, &weight);
        printf("%d and %d, length is %d\n", node_1, node_2, weight);
        addEdge(node_1, node_2, weight, graph);
    }
    int i;
    for (i = 0; i < vertexs; ++i)
    {
    	struct AdjNode* node = graph->vertexs[i].head;
    	printf("vertex: %d\n", i+1);
    	while(node->next != NULL)
    	{
    		node = node->next;
    		printf("->%d\n", node->id);
    	}
    	printf("\n");
    }
    int src_node, des_node;
    /* find the shortest path from A to B */
    printf("Please type the source vertex number: ");
    scanf("%d", &src_node);
    printf("Please type the destination vertex number: ");
    scanf("%d", &des_node);
    dijkstra(graph, src_node, des_node);

	return 0;
}