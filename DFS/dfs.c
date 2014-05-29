#include <stdio.h> 
#include <stdlib.h>
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
	while ((read = getline(&line, &len, fp)) != -1) 
	{
		//printf("Retrieved line of length %zu :\n", read);
        //printf("%s", line);
        sscanf(line, "%d %d", &node_1, &node_2);
        printf("%d and %d\n", node_1, node_2);
    }
    if(line)
    	free(line);
	return 0;
}