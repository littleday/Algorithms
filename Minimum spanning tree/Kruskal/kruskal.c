/***
* Kruskal Algorithm: 
* Minimum spanning tree of connected weighted undirect graph
* 
* Note: the format of test.txt is: vertex_1 vertex_2 weight 
* for all edges, find the shortest edges
*   Add to relatived vertexts to solved list
*   if there is a loop, ignore this edge
***/
#include <stdio.h> 
#include <stdlib.h>
#define N 5; // vertexs' number

/*** Implement Graph using adjancent linked list ***/

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

void kruskal(struct Graph* graph)
{
    int number = graph->number;
    int records[number][number];
        int j,k;
        for (j = 0; j < number; ++j)
            for (k = 0; k < number; k++)
            {
                records[j][k] = 0;
            }
    int i;
    for (i = 0; i < number; ++i)
    {
        struct AdjNode * vertex = graph->vertexs[i].head;
        struct AdjNode * temp = vertex;
        while (temp->next != NULL)
        {
            temp = temp->next;
            records[i][temp->id-1] = temp->weight;
        }
    }
    int solved[number];
    for (i = 0; i < number; ++i)
    {
        solved[i] = 0;
    }

    int size = 0;
    while(size <= number)
    {
        int temp_begin = -1;
        int temp_end = -1;
        int temp_weight = 1000000; // Max
        int m, n;
        for (m = 0; m < number; ++m)
        {
            for (n = 0; n < number; ++n)
            {
                if (records[m][n] != 0)
                {
                    if (records[m][n] < temp_weight)
                    {
                        temp_begin = m+1;
                        temp_end = n+1;
                        temp_weight = records[m][n];
                    }
                }
            }
        }
        //printf("Current vertexs are %d and %d with weight %d\n", temp_begin, temp_end, temp_weight);
        printf("Is%d and %d\n",solved[temp_begin-1], solved[temp_end-1]);
        if (solved[temp_begin-1] == 0 && solved[temp_end-1] == 0)
        {
            solved[temp_begin-1] = 1;
            printf("One Vertex %d is \n", temp_begin);
            size++;
            solved[temp_end-1] = 1;
            printf("One Vertex %d is \n", temp_end);
            size++;
            printf("This edge weight is %d\n", temp_weight);
            records[temp_begin-1][temp_end-1] = 0;
        }
        else
        {
            if (solved[temp_begin-1] == 0)
            {
                solved[temp_begin-1] = 1;
                printf("One Vertex %d is \n", temp_begin-1);
                size++;
                printf("One Vertex %d is \n", temp_end-1);
                printf("This edge weight is %d\n", temp_weight);
                records[temp_begin-1][temp_end-1] = 0;
            }
            if (solved[temp_end-1] == 0)
            {
                solved[temp_end-1] = 1;
                printf("One Vertex %d is \n", temp_begin-1);
                printf("One Vertex %d is \n", temp_end-1);
                size++;
                printf("This edge weight is %d\n", temp_weight);
                records[temp_begin-1][temp_end-1] = 0;
            }
        }

    }
}
int main(int argc, char const *argv[])
{
    FILE *fp = NULL;
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
    kruskal(graph);
    return 0;
}