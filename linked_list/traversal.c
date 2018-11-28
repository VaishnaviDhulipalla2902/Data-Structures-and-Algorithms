#include<stdio.h>
struct node{
    int data;
    struct node *next;
};
/*bool search(struct node* head,int x){
    while(head != NULL){
        if(head -> data == x) return true;
        head = head -> next;
    }
    return false;
} */
int search(struct node* head,int x){
    if(head == NULL) return 0;
    else{
        while(head != NULL){
            if(head -> data == x) return 1;
            head = head ->next;
        }
        return 0;
    }
    
}