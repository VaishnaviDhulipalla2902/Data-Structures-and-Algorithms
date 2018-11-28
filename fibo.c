#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>


int findMod(int arr[],int digits, int divisor)
{
    int i=0,num;
    while(i<digits)
    {
        num = arr[i];
        while(num<divisor && i<digits)
        {
            i++;
            num = num*10 + arr[i];
        }
        printf("num = %d\n",num);
        arr[i] = num%divisor;
    }
    return num/10;
}

int findFib(int n[],int m,int len)
{
    if((n[0]==0 || n[0]==1) && len==1) return n[0];
    int fib0 = 0;
    int fib1 = 1;
    int result = 0;
    int i=len-1;
    int count=0;
    int period = -1;
    while(i>=0)
    {
        //printf("count = %d\n",count);
        int val = n[i]*(pow(10,i));
        if(i==0)
        {
            while(val>=2)
            {
                result = (fib0 + fib1)%m;
                fib0 = fib1;
                fib1 = result;
                val--;
                count++;
            }
            i--;  
        }
        else
        {
            while(val>=0)
            {
                result = (fib0 + fib1)%m;
                fib0 = fib1;
                fib1 = result;
                val--;
                count++;
            }
            i--;
        }
        if(fib0 == 0 && fib1==1 && period==-1)
        {
            period = count+1;
            break;
        }
    }
    if(period!=-1) result = 
    return result;
}



int main()
{
    int n[100000] ,m;
    printf("enter modulo number\n");
    scanf("%d",&m);
    printf("enter the index of fibo number u want\n");
    char* s = (char*)malloc(100000*sizeof(char));
    scanf("%s",s);
    int len = strlen(s);
    for(int i=0,j=len-1;i<strlen(s);i++,j--)
    {
        n[i] = atoi(&s[j]);
    }
    free(s);
    int result = findFib(n,m,len);
    printf("%d\n",result);
    return 0;
}