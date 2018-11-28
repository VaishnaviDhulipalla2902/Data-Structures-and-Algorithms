#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *next;
};
int addatbeg(struct node**,int);
int main(){
    int i,key;
    struct node* head = NULL,*temp=NULL;
    struct node* current= head;
    int counter,size;
    printf("Enter the number of elements:\n");
    scanf("%d",&size);  
    printf("Enter elements of linkedlist:\n");
    for(i=0;i<size;i++){
        temp = malloc(sizeof(struct node));
        scanf("%d",&temp->data);
        temp->next=NULL;
        if(head==NULL)
        {
            head=temp;
            current=head;
        }
        else
        {   
            current->next=temp;
            current=temp;
        }
    }
    current = head;
    while(current!=NULL){
        printf("%d\t",current->data);
        current= current->next;
    }
    printf("Enter the key to be added:");
    scanf("%d",&key);
    int addatbeg(struct node **head,int key);
    
    while(head!=NULL){
        printf("%d\t",head->data);
        head = head->next; } 
    return 0;     

}


int addatbeg(struct node** head,int key){
    struct node *temp;
    temp = malloc(sizeof(struct node));
    temp -> data = key;
    temp -> next = *head;
    *head = temp;
}