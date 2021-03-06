#include<stdio.h>
#include<stdlib.h>

int swap(int arr[],int i,int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    return 0;
}

int bottomUpHeapify(int i,int heap[])
{
    int p = (i-1)/2;
    while(i>0 && heap[i]<heap[p])
    {
        swap(heap,i,p);
        i = p;
        p = (i-1)/2;
    }
    return 0;
}

int topDownHeapify(int i,int heap[],int n)
{
    //printf("%d\n",n);
    int l = 2*i + 1;
    int r = 2*i + 2;
    int min;
    while(r<n)
    {
        if(heap[l]<heap[r]) min = l;
        else min = r;
        if(heap[i]>heap[min]){
            swap(heap,i,min);
            i = min;
            l = 2*i + 1;
            r = 2*i + 2;
        }
        else break;
    }
    if(l<n && heap[i]>heap[l])
    {
        swap(heap,i,l);
    }
    return 0;
}

int delMin(int heap[],int* n)
{
    int min = heap[0];
    swap(heap,0,(*n)-1);
    *n -= 1;
    topDownHeapify(0,heap,*n);
    return min;
}

int increaseKey(int heap[], int i, int num, int n)
{
    if(heap[i]<num)
    {
        heap[i] = num;
        topDownHeapify(i,heap,n);
    }
    return 0;
}

int decreaseKey(int heap[], int i, int num)
{
    if(heap[i]>num)
    {
        heap[i] = num;
        bottomUpHeapify(i,heap);
    }
    return 0;
}

int changeKey(int heap[], int i,int num, int n)
{
    if(heap[i]>num)
    {
        decreaseKey(heap,i,num);
    }
    else
    {
        increaseKey(heap, i, num,n);
    }
    return 0;
}

int main()
{
    int heap[10000];
    int n = 0;
    printf("enter 1 to add, 0 to exit\n");
    int ans;
    scanf("%d",&ans);
    while(ans)
    {
        printf("enter the number to add to the heap\n");
        scanf("%d",&heap[n++]);
        bottomUpHeapify(n-1,heap);
        printf("enter 1 to add, 0 to exit\n");
        scanf("%d",&ans);
    }
    printf("the heap in level order is\n");
    for(int i=0;i<n;i++)
    {
        printf("%d ",heap[i]);
    }
    printf("\n");
    printf("enter the index which has to be changed\n");
    int k;
    scanf("%d",&k);
    int num;
    printf("enter the number to which it has to be changed\n");
    scanf("%d",&num);
    changeKey(heap, k,num,n);
    printf("the heap in level order after change is\n");
    for(int i=0;i<n;i++)
    {
        printf("%d ",heap[i]);
    }
    printf("\n"); 
    return 0;
}