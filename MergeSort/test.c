# include <stdio.h>
# include <string.h>
# include <stdlib.h>
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
int main(int argc, char const *argv[])
{

	int n1[] ={2,3,5};
	int n2[] ={3,6,7,8};
	int *n3 = merge(n1, 3, n2, 4);
	int i;
	for (i = 0; i < 7; ++i)
	{
		printf("%d ",n3[i]);
	}
	printf("\n");
	return 0;
}