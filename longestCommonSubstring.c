#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { false, true } bool;

struct node{
        int data;
        struct node *next;
};
int hash(int num, int MOD){
    return (num % MOD);
}
bool search(struct node *head, int data){
    while(head != NULL){
        if(data == head->data) return true;
        head = head->next;
    }
    return false;
}
void addAtBeg(struct node **head, int key){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = key;
    temp->next = *head;
    *head = temp;
}
int main(){
    int A = 0, B = 0, h = 1, d, n, m, l, p, ini = 0, fin = 0, pos, i , j, flag = 0;
    char *T, *P;
    T = (char *)malloc(1000000*sizeof(char));
    P = (char *)malloc(1000000*sizeof(char));
    scanf("%s %s", T, P);
    n = strlen(T);
    m = strlen(P);
    scanf("%d %d", &d, &p);
    l = m/2;
    struct node **hashTable;
    hashTable = (struct node **)malloc(p*sizeof(struct node *));
    while(l > 0 && l <= m){
        int A = 0, B = 0, h = 1;
        hashTable = (struct node **)malloc(p*sizeof(struct node *));
        for(i = 0; i < l; i++){
            A = (P[i] + A*d)%p;
            B = (T[i] + B*d)%p;
            h = (h*d)%p;
        }
        //printf("A: %d, B: %d\n", A, B);

        for(i = 0; i <= m-l; i++){
            printf("hash(A): %d, i : %d\n", hash(A,p), i);
            addAtBeg(&hashTable[hash(A,p)],A);
            A = (((A*d)%p + (P[i+l])%p)%p - (P[i]*h)%p)%p;
            //printf("A: %d, B: %d\n", A, B);
            if(A < p) A += p;
        }

        for(i = 0; i <= n-l; i++){
            printf("hash(B): %d, i : %d\n", hash(B,p), i);
            //printf("hash(A): %d, hash(B): %d, i : %d\n", hash(A,p), hash(B,p), i);
            if(search(hashTable[hash(B,p)],B)){
                //printf("hash(B): %d, i : %d\n", hash(B,p), i);
                flag = 1;
                ini = i+1;
                fin = l-ini;
                // for(j = 0; j < l; j++){
                //     if(T[i+j] != P[j]) break;
                // }
                // if(j == l){
                //     flag = 1;
                //     fin = i;
                //     ini = j;
                // } 
            }

            B = (((B*d)%p + (T[i+l])%p)%p - (T[i]*h)%p)%p;
            //printf("A: %d, B: %d\n", A, B);
            if(B < p) B += p;
        }
        if(flag) l = l + l/2;
        else l = l - l/2;
    }
    if(flag){
        printf("%d %d\n", ini, fin);
        for(i = ini; i < fin; i++){
            printf("%d ", T[i]);
        }
    }
    else printf("No!");
    return 0;

}


