#include <stdio.h>
#include <stdlib.h>


void push(int *S, int *top, int key){
    *top = *top + 1;
    S[*top] = key;
    return;
}

int pop(int *S, int *top){
    if(*top == -1) return 0;
    *top = *top - 1;
    return S[(*top) + 1];
}

int largestRectangle(int n, int* h) {
    int p, i, max = 0, *S, top, rec;
    S = (int *)malloc(n*sizeof(int));
    top = -1;
    while (i < n)
    {
        if (top == -1 || h[S[top]] <= h[i])
            push(S, &top, i++);
        else
        {
            p = S[top];
            pop(S, &top);
            rec = h[p] * (top == -1 ? i : i - S[top] - 1);
            if (max < rec)
                max = rec;
        }
    }
    while (top != -1)
    {
        p = S[top];
        pop(S, &top);
        rec = h[p] * (top == -1 ? i : i - S[top] - 1);
 
        if (max < rec)
            max = rec;
    }
 
    return max;
    
}

int main() {
    int n, m; 
    scanf("%i %i", &n, &m);
    int **land = (int **)malloc(n*sizeof(int *));
    for(int i = 0; i < n; i++){
        land[i] = (int *)malloc(m*sizeof(int));
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            scanf("%d",&land[i][j]);
        }
    }
    int **land1 = (int **)malloc(n*sizeof(int *));
    for(int i = 0; i < n; i++){
        land1[i] = (int *)malloc(m*sizeof(int));
    }
    for(int j = 0; j < m; j++){
            land1[0][j] = land[0][j];
    }
    for(int j = 0; j < m; j++){
        for(int i = 1; i < n; i++){
            land1[i][j] = land1[i-1][j] + land[i][j];
        }
    }
    int max = 0, result = 0;
    for(int i = 0; i < n; i++){
        int *h = malloc(sizeof(int) * m);
        for(int j = 0; j < m; j++){
            h[j] = land1[i][j];
        }
        result = largestRectangle(m,h);
        if(result > max) max = result;
    }
    printf("%d\n",max);
    return 0;
}
