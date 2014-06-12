/***
* Prim Algorithm: 
* Minimum spanning tree of connected weighted undirect graph
* 
* Note: the format of test.txt is: vertex_1 vertex_2 weight 
***/
#include <stdio.h> 
#include <stdlib.h>
#define N 6; // vertexs' number

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

void prim(struct Graph*graph, int beginner)
{
    int number = graph->number;
    int size = 1;
    int *solved = (int *)malloc(sizeof(int) * size);
    solved[0] = beginner;
    while (size != number)
    {
        int i;
        int records[number][number];
        int j,k;
        for (j = 0; j < number; ++j)
            for (k = 0; k < number; k++)
            {
                records[j][k] = 0;
            }
        // Add the solved nodes and their adjancent nodes, weights to records table 
        for (i=0; i<size; i++)
        {
            struct AdjNode * vertex = graph->vertexs[solved[i]-1].head;
            struct AdjNode * temp = vertex;
            while (temp->next != NULL)
            {
                temp = temp->next;
                int flag = 0;
                for (j = 0; j < size; ++j)
                {
                    if (solved[j] == temp->id)
                    {
                        flag++;
                    }
                }
                if (flag == 0)
                {
                    records[i][temp->id-1] = temp->weight;
                    printf("Add %d to %d with weight %d to record table:\n", i+1, temp->id, temp->weight);
                }
            }

        }
        // Travesal the records table to find next shortest path
        int temp_begin = 0;
        int temp_end = 0; 
        int temp_path = 100000;
        for (j = 0; j < number; ++j)
        {
            for (k = 0; k < number; ++k)
            {
                if (records[j][k] < temp_path)
                {
                    temp_begin = j + 1;
                    temp_end = k + 1;
                    temp_path = records[j][k];
                }
            }
        }
        printf("Next path is from Vertext %d to Vertext %d with Weight %d\n", temp_begin, temp_end, temp_path);
        size++;
        solved = (int *)realloc(solved, sizeof(int) * size);
        solved[size-1] = temp_end;
        int x;
        for ( x= 0; x< size; x++)
        {
            printf("Test: solved[x]:\n");
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
    int src_node;
    printf("Please type the source vertex number: ");
    scanf("%d", &src_node);
    prim(graph, src_node);
    return 0;
}