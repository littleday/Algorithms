# include <stdio.h>
# include <string.h>
# include <stdlib.h>
#define N 4
int *merge(int * left, int len_1, int * right, int len_2)
{
    int *newLine = (int *) malloc((len_1 + len_2)* sizeof(int));
    int i,j,k;
    i = 0;
    j = 0;
    for (k = 0; k < len_1 + len_2; ++k)
    {
        if (i >= len_1)
        {
            newLine[k] = right[j];
            j++;
        } 
        else if (j >= len_2)
        {
            newLine[k] = left[i];
            i++;
        } 
        else
        {
            if (left[i] < right[j])
            {
                newLine[k] = left[i];
                i++;
            }
            else
            {
                newLine[k] = right[j];
                j++;
            }
        }
    }
        return newLine;
}

void mergesort(int * List, int l, int r)
{
    if (l == r)
    {
        return;
    }
    else
    {
    int m = (l + r)/2;
    int * left = (int *) malloc((m - l+1)* sizeof(int));
    int * right = (int *) malloc((r - m)* sizeof(int));
    int * tmp = NULL;
    memcpy(left, List + l, sizeof(int)*(m-l+1));
    memcpy(right, List + m + 1, sizeof(int)*(r-m));
    mergesort(left, 0, m-l);
    mergesort(right, 0, r-m-1);
    tmp = merge(left, m-l+1, right, r-m);
    memcpy(List, tmp, (r - l + 1) * sizeof(int)) ;
}
}
int main(int argc, char const *argv[])
{
	printf("Please enter a list you want to sort with the length of %d : \n", N);
	int numbers[N];
	//numbers = (int *) malloc (N * sizeof(int));
	int i;
	for (i = 0; i < N; ++i)
	{
		scanf ("%d", &numbers[i]);
	}

	mergesort(numbers, 0, N-1);

	for (i = 0; i < N; ++i)
	{
		printf("%d ",numbers[i]);
	}
	printf("\n");
	return 0;
}