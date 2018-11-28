#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
};
int addatend(struct node **head,int key){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp -> data = key;
    if(*head == NULL){ 
        *head = temp;
        return ;
    }
    else{
        while(head != NULL) head = head -> next;        
        head -> next = temp;
        temp -> next = NULL;
        return ;
    }
    return 0;
}