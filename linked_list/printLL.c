#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node* next;
};
struct node * createLL(int);
void printLL(struct node*);
int main(){
    int n;
    struct node *head = NULL;
    printf("Number of nodes:");
    scanf("%d",&n);
    head = createLL(n);
    printLL(head);
    return 0;
}
struct node * createLL(int n){
    int i = 0;
    struct node * headL, *temp = NULL, *current = NULL;
    while(i<n){
        temp = (struct node*)malloc(sizeof(struct node));
        scanf("%d",&(temp->data));
        
        if(head == NULL) head = temp;
        else{
            current = head;
            while(current->next != NULL){
                current = current->next;
                current->next = temp;
            }
        } i++;
    }
    return head;
}
void printLL(struct node* head){
    struct node *current = head;
    while(current != NULL){
        printf("%d\t",current->data);
        current = current->next;
    }
}