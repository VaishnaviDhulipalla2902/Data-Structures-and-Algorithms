#include<stdio.h>
#include<stdlib.h>
struct node{ 
    int data;
    struct node *next;
};
int addatposn(struct node **,int key,int n){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp -> data = key;
    if (head == NULL){
        temp -> next = NULL;
        return;
    }
    if (n == 0){
        temp -> next = head;
        return;
    }
    else{
        while(n > 0){
            head = head -> next;
            n --;
        }
        temp -> next = head -> next;
        head -> next = temp;
    }
    return 0;
}