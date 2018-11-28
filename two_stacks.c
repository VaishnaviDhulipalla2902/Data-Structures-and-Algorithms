#include<stdio.h>
#include<stdlib.h>
int push(int*, int, int*);
int pop(int*, int*);
int push(int* ar,int x, int* top)
{
       *top = *top + 1;
        ar[*top] = x;
        return 0;
}
int pop(int* ar, int* top)
{
    int num = ar[*top];
    *top = *top - 1;
     return num;
}
int main(){
    int n,temp,num,d,min;
    int* s1,*s2;
    int* top1 ,*top2;
    top1 = (int*)malloc(sizeof(int));
    top2 = (int*)malloc(sizeof(int));
    *top1 = -1;
    *top2 = -1;
    scanf("%d",&n);
    s1 = (int*)malloc(n * sizeof(int));
    s2 = (int*)malloc(n * sizeof(int));
    for(int i = 0;i<n;i++){
        scanf("%d",&temp);
        if(temp == 1){
            scanf("%d",&d);
            push(s1,d,top1);
        }
        if(temp == 2){
            if(*top2 == -1){ 
                while(*top1 != -1){
                   num = pop(s1,top1);
                   push(s2,num,top2);
                }
            }            
           printf("%d\n",pop(s2,top2));
        }
        if(temp == 3){
            if(*top1 != -1) min = s1[*top1];
            else min = s2[*top2];
            while(*top1 != -1){
                num = pop(s1,top1);
                push(s2,num,top2);
            }
            while(*top2 != -1){
                num = pop(s2,top2);
                if(min >= num) min = num;
                push(s1,num,top1);
            }
            printf("%d\n",min);        

        }       
    }
    return 0;
}