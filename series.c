#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int identity(int** x)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(i==j)
            {
                x[i][j] = 1;
            }
            else
            {
                x[i][j] = 0;
            }
        }
    }
    return 0;
}

int** matrixMulti(int** a, int** b)
{
    printf("the first matrix\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    printf("the second matrix\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("%d ",b[i][j]);
        }
        printf("\n");
    } 
    int **c = (int **)malloc(3 * sizeof(int *));
    for (int i=0; i<3; i++)
        c[i] = (int *)malloc(3 * sizeof(int));
    int i,j,k;
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            for(k=0;k<3;k++)
                c[i][j] += a[i][k] + b[k][j];
                printf("c[%d][%d] = %d\n",i,j,c[i][j]);  
    printf("the product matrix\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("%d ",c[i][j]);
        }
        printf("\n");
    } 
    return c;
}

int** p(int **base, int power[], int n)
{
    int **result = (int **)malloc(3 * sizeof(int *));
    for (int i=0; i<3; i++)
         result[i] = (int *)malloc(3 * sizeof(int));
    identity(result);
    int **x = (int **)malloc(3 * sizeof(int *));
    for (int i=0; i<3; i++)
         x[i] = (int *)malloc(3 * sizeof(int));
    for(int i=n-1;i>=0;i--)
    {
        identity(x);
        while(power[i]--)
        {
            x = matrixMulti(x,base);
        }
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                printf("%d ",x[i][j]);
            }
            printf("\n");
        }
        result = matrixMulti(result,x);
        int i = 10;
        identity(x);
        while(i--)
        {
            x = matrixMulti(x,base);
        }
        base = x;
    }
    for (int i=0; i<10; ++i) {
        free(x[i]);
    }
    free(x);
    return result;
}

int series(int n[],int length)
{
    int **A = (int **)malloc(3 * sizeof(int *));
    for (int i=0; i<3; i++)
         A[i] = (int *)malloc(3 * sizeof(int));
    A[0][0] = 1;
    A[0][1] = 1;
    A[0][2] = 0;
    A[1][0] = 0;
    A[1][1] = 1;
    A[1][2] = 1;
    A[2][0] = 0;
    A[2][1] = 1;
    A[2][2] = 0;
    int **powerMatrix = (int **)malloc(3 * sizeof(int *));
    for (int i=0; i<3; i++)
        powerMatrix[i] = (int *)malloc(3 * sizeof(int));
    powerMatrix = p(A,n,length);
    int num1 = 2*powerMatrix[2][0];
    int num2 = powerMatrix[2][1];
    for (int i=0; i<10; ++i) {
        free(powerMatrix[i]);
    }
    free(powerMatrix);
    for (int i=0; i<10; ++i) {
        free(A[i]);
    }
    free(A);
    return num1 + num2;
}

int main()
{
    char n[1000];
    printf("enter a number\n");
    scanf("%s",n);
    int num[1000],i;
    for(i=0;i<strlen(n);i++)
    {
        num[i] = n[i] - '0';
    }
    printf("the nth number of the series is %d\n",series(num,i));
    return 0;
}