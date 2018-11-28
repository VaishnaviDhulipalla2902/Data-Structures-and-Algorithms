#include <stdio.h>
#include <stdlib.h>

void merge(int arr[],int l,int m, int r)
{
  int result[100000];
  int i=l,j=m+1,k=0;
  while(i<m+1 && j<=r)
  {
    if(arr[i]<arr[j])
    {
      result[k] = arr[i];
      k++;
      i++;
    }
    else
    {
      result[k] = arr[j];
      k++;
      j++;
    }
  }
  while(i<=m)
  {
    result[k] = arr[i];
    k++;
    i++;
  }
  while(j<=r)
  {
    result[k] = arr[j];
    j++;
    k++;
  }

  int z=0;
  int p=l;
  while(p<=r)
  {
    arr[p] = result[z];
    z++;
    p++;
  }
}
void mergesort(int arr[],int l, int r)
{
  int m = (r+l)/2;
  if(l==r)
    return;
  else
  {
  //  printf("l=%d m=%d r=%d\n",l,m,r);
    mergesort(arr,l,m);
    mergesort(arr,m+1,r);
    //printf("yo\n");
    merge(arr,l,m,r);
  }
}


int main(){
  long long n, k;
  scanf("%lld %lld", &n,&k);
  int *A = (int *)malloc(2*k*sizeof(int));
  for(long long j = 0; j < 2*k; j++){
    int r = rand()%50 + 23;
    A[j] = r;
  }
  for(long long i = 0; i < (n/k); i++){
    mergesort(A,0,2*k-1);
    for(long long j = 0; j < k; j++){
      int r = rand()%50 +23;
      A[j+k] = r;

    }
  }
  mergesort(A,0,2*k-1);
  for(long long j = 0; j < k; j++){
    printf("%d ", A[j]);
  }
  return 0;
}
