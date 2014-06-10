#include <stdio.h>
#include <stdlib.h>
#define LEN 100000
int main(int argc, char const *argv[])
{
    /* Read from File */
    FILE *fp = NULL; // Pointer must be initialized
    char *line = NULL;
    size_t len;
    ssize_t read;
    int array[LEN];
    fp = fopen("IntegerArray.txt", "r");
    if ( fp == NULL )
        exit(1);
    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        //printf("Retrieved line of length %zu :\n", read);
        //printf("%s", line);
        sscanf(line, "%d", &array[i]);
        i++;
        printf("Have read %d lines!\n", i);
    }

    /*

    for (i = 0; i < LEN; i++) {
        printf("%d\n", array[i] );
    }

    */
    long count = 0; // int is smaller for the estimated result: 5,0000,00000, which can be checked in limits.h
    int m, n;
    for( m = 0; m < LEN-1; m++)
    {
        for(n = m+1; n < LEN; n++)
        {
            if (array[m] > array[n])
                count = count + 1;
        }
    }
    printf("There are %lu inversions in this array!\n", count);

    return 0;
}
