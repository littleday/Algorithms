# include <stdio.h>
# include <string.h>
#define N 4
void quicksort(int * List, int left, int right)
{
	int pivot, m , n, temp;
    if (left < right)
    {
        pivot = left; //leftmost
        m = left;
        n = right;
        while(m < n){
        	while(List[m]<=List[pivot] && m < right)
        		m++;
        	while(List[n] > List[pivot])
        		n--;
        	if (m < n)
        	{
        		temp = List[m];
        		List[m] = List[n];
        		List[n] = temp;
        	}
        }
        temp = List[pivot];
        List[pivot] = List[n];
        List[n] = temp;
        quicksort(List, left, n - 1);
        quicksort(List, n + 1, right);
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

	quicksort(numbers, 0, N-1);

	for (i = 0; i < N; ++i)
	{
		printf("%d ",numbers[i]);
	}
	printf("\n");
	return 0;
}