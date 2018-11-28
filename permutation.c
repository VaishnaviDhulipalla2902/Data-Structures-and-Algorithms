#include<stdio.h>
#include<stdlib.h>
struct Stack
{
    int top;
    unsigned capacity;
    int* array;
};
struct Queue
{
    int front, rear, size;
    unsigned capacity;
    int* array;
};
int isFull(struct Queue*);
int isEmpty(struct Queue*);
void enqueue(struct Queue*, int);
int dequeue(struct Queue*);
int isfull(struct Stack*);
int isempty(struct Stack*);
void push(struct Stack*, int); 
int pop(struct Stack*);
int isPossible(struct Queue*,struct Queue*,int);
int main(){
    int n, i, value[n];
    struct Queue* input = malloc(sizeof(struct Queue));
    struct Queue* output = malloc(sizeof(struct Queue));
    printf("Enter capacity:");
    scanf("%d",&n);
    input->capacity = n;
    output->capacity = n;
    input->size = input->front = 0;
    output->size = output->front = 0;
    input->rear = n - 1;
    output->rear = n - 1;
    input->array = (int*)malloc(input->capacity * sizeof(int));
    output->array = (int*)malloc(input->capacity * sizeof(int));
    for(i = 0;i<n;i++){
       enqueue(input,i+1);
    }
    for(i=0;i<n;i++){
        scanf("%d",value+i);
    }
    for(i=0;i<n;i++){
        enqueue(output,value[i]);
    }
    for(int i = 0; i < n; i++)
    {
        printf("%d %d\n",output->array[i], input->array[i]);
    }
    if(isPossible(input,output,n) == 1){
        printf("True");
    }
    else{
        printf("False");
    }
    return 0;
}
int isFull(struct Queue* queue){
      return (queue->size == queue->capacity); 
 }
int isEmpty(struct Queue* queue){
      return (queue->size == 0);
 }
 
void enqueue(struct Queue* queue, int item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)%queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
   
}
 
int dequeue(struct Queue* queue){
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)%queue->capacity;
    queue->size = queue->size - 1;
    return item;
}
int isfull(struct Stack* stack){
       return stack->top == stack->capacity - 1; 
}
 
int isempty(struct Stack* stack){
       return stack->top == -1; 
 }
 
void push(struct Stack* stack, int item){
    if (isfull(stack))
        return ;
    stack->array[++stack->top] = item;
    
}

int pop(struct Stack* stack)
{
    if (isempty(stack))
        return -1;
    return stack->array[stack->top--];
}

int isPossible(struct Queue* input,struct Queue* output,int capacity){
    for(int i = 0; i < 3; i++)
    {
        printf("%d %d\n",output->array[i], input->array[i]);
    }
    struct Stack* stack = malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    while(!isEmpty(input)){
        if(input->array[input->front] == output->array[output->front]){
            dequeue(input);
            dequeue(output);
            if(stack->array[stack->top] == output->array[output->front]){
                pop(stack);
                dequeue(output);
            }
            
        }
        else{
            push(stack,input->array[input->front]);
            dequeue(input);
        }

    }
    if(isEmpty(input) && isempty(stack)) return 1;
    else return 0;

}
   

  