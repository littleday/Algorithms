#include <stdio.h> 
#include <stdlib.h>
#define LEN 6
int main(int argc, char const *argv[])
{
	/* Read from File */
	FILE *fp;
	char *line;
	size_t len;
	ssize_t read;
	int array[LEN];
	fp = fopen("test.txt", "r");
	if ( fp == NULL )
		exit(1);
	int i = 0;
	while ((read = getline(&line, &len, fp)) != -1) 
	{
		//printf("Retrieved line of length %zu :\n", read);
        //printf("%s", line);
        sscanf(line, "%d", &array[i]);
        i++;
    }
    for (i = 0;i < LEN;i++){
    	printf("%d\n", array[i] );
    }
    int count = 0;
    int m=0;
    int n = 0;
    for( m = 0; m < LEN-1; m++)
    {
    	printf("%d\n", m );
    	for(n = 0; n < LEN; n++)
    	{
    		if (array[m] > array[n])
    			count = count + 1;
    		printf("%d\n", n);
    	}
    }
    printf("%d\n", count);
	return 0;
}