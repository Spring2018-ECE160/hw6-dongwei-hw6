#include<stdio.h>

#define MAXSIZE 1000

void range(int x[],int n,int *max_ptr,int *min_ptr);

int main()
{
   int A[MAXSIZE];
   int i,n;
   int count, largest, smallest;
   count = n;
   printf("How many numbers do you wanna input ?");
    scanf("%d",&count);
   printf("Enter %d numbers to find the maximum and minimum", count);
    for(i=0;i<count;i++)
    {
        scanf("%d",&A[i]);
    }
   range(A,count,&largest,&smallest);
   printf("largest=%d, smallest=%d\n", largest, smallest);

}




void range(int x[],int n,int *max_ptr,int *min_ptr)
{
  int k,min,max;

  min = x[0];
  max = x[0];

  for(k = 1; k < n; k++) {
    if(x[k] > max)
      max = x[k];
    else if(x[k] < min)
      min = x[k];
    }

  *max_ptr = max;
  *min_ptr = min;
}