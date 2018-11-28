#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 10000000

struct node
{
    int index;
    int vertex;
    int d;
    int f;
    struct node* next;
    struct node* parent;
    int p;
};


int swap(struct node* arr[],int i,int j)
{
    struct node* temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    return 0;
}

int bottomUpHeapify(int i,struct node* heap[])
{
    int parent = (i-1)/2;
    while(i>0 && heap[i]->p<heap[parent]->p)
    {
        swap(heap,i,parent);
        i = parent;
        parent = (i-1)/2;
    }
    return i;
}

int decreaseKey(struct node* heap[], int i, int num)
{
    if(heap[i]->p>num)
    {
        heap[i]->p = num;
        bottomUpHeapify(i,heap);
    }
    return i;
}

int add(struct node* heap[], int* n, struct node* num)
{
    heap[(*n)++] = num;
    return bottomUpHeapify(*n-1,heap);;
}

int topDownHeapify(int i,struct node* heap[],int n)
{
    //printf("%d\n",n);
    int l = 2*i + 1;
    int r = 2*i + 2;
    int min;
    while(r<n)
    {
        if(heap[l]->p<heap[r]->p) min = l;
        else min = r;
        if(heap[i]->p>heap[min]->p){
            swap(heap,i,min);
            i = min;
            l = 2*i + 1;
            r = 2*i + 2;
        }
        else break;
    }
    if(l<n && heap[i]->p>heap[l]->p)
    {
        swap(heap,i,l);
    }
    return 0;
}

struct node* delMin(struct node* heap[],int* n)
{
    struct node* min = heap[0];
    swap(heap,0,(*n)-1);
    *n -= 1;
    topDownHeapify(0,heap,*n);
    return min;
}

struct node* createNode(int v)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    newNode->p = INF;
    return newNode;
}

struct Graph
{
    int numVertices;
    struct node** adjLists;
    int** weightLists;
    char** color;
};

struct Graph* createGraph(int vertices)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    
    graph->adjLists = malloc(vertices * sizeof(struct node*));
    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    graph->weightLists = (int**)malloc(vertices*sizeof(int*));

    for (i = 0; i < vertices; i++) {
        graph->weightLists[i] = (int*)malloc(vertices*sizeof(int));
    }

    graph->color = (char**)malloc(vertices*sizeof(char*));
    for(int i=0;i<=vertices;i++)
    {
        graph->color[i] = (char*)malloc(7*sizeof(char));
        graph->color[i] = "red";
    }
    
    return graph;
}

void addEdge(struct Graph* graph, struct node* src, struct node* dest, int weight)
{
    // Add edge from src to dest
    struct node* newNode1 = createNode(dest->vertex);
    if(graph->adjLists[src->vertex]==0)
    {
        graph->adjLists[src->vertex] = newNode1;
    }
    else{
        newNode1->next = graph->adjLists[src->vertex];
        graph->adjLists[src->vertex] = newNode1;
    }
    graph->weightLists[src->vertex][dest->vertex] = weight;
    // Add edge from dest to src

    struct node* newNode2 = createNode(src->vertex);
    if(graph->adjLists[dest->vertex]==0)
    {
        graph->adjLists[dest->vertex] = newNode2;
    }
    else{
        newNode2->next = graph->adjLists[dest->vertex];
        graph->adjLists[dest->vertex] = newNode2;
    }
    graph->weightLists[dest->vertex][src->vertex] = weight;
}

void printGraph(struct Graph* graph)
{
    int n = graph->numVertices;
    for(int i=0;i<n;i++)
    {
        struct node* temp = graph->adjLists[i];
        printf("%d:",i);
        while(temp)
        {
            printf("%d->",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

int Dijkstra(struct Graph* graph,struct node* s, struct node* heap[], int n, struct node* vertices[])
{
    graph->color[s->vertex] = "yellow";
    s->parent = s;
    s->p = 0;
    s->index = add(heap, &n, s);
    while(n>0)
    {
        printf("n = %d\n",n);
        struct node* u = delMin(heap,&n);
        printf("u = %d\n",u->vertex);
        graph->color[u->vertex] = "blue";
        printf("min distance = %d\n",vertices[u->vertex]->p);
        struct node* temp = graph->adjLists[u->vertex];
        while(temp)
        {
            printf("temp = %d\n",temp->vertex);
            if(!strcmp(graph->color[temp->vertex],"red"))
            {
                graph->color[temp->vertex] = "yellow";
                vertices[temp->vertex]->parent = u;
                vertices[temp->vertex]->p = u->p + graph->weightLists[u->vertex][temp->vertex];
                vertices[temp->vertex]->index = add(heap, &n, vertices[temp->vertex]);
                printf("temp->p = %d\n",temp->p);
            }
            else if(!strcmp(graph->color[temp->vertex],"yellow"))
            {
                if(vertices[temp->vertex]->p > u->p + graph->weightLists[u->vertex][temp->vertex])
                {
                    vertices[temp->vertex]->p = u->p + graph->weightLists[u->vertex][temp->vertex];
                    vertices[temp->vertex]->parent = u;
                    vertices[temp->vertex]->index = decreaseKey(heap, vertices[temp->vertex]->index, vertices[temp->vertex]->p);
                }
            }
            temp = temp->next;
        }
    }
}

int main()
{
    printf("enter num of nodes\n");
    int n;
    scanf("%d",&n);
    struct Graph* graph = createGraph(n+1);
    struct node* vertices[n+1];
    for(int i=0;i<=n;i++) vertices[i] = 0;
    printf("enter num of edges\n");
    int edges;
    struct node* heap[edges];
    scanf("%d",&edges);
    printf("enter the edges\n");
    while(edges--)
    {
        int start, end, weight;
        scanf("%d %d %d",&start,&end,&weight);
        start--;
        end--;
        if(!vertices[start]) 
        {
            vertices[start] = createNode(start);
        }
        if(!vertices[end]) 
        {
            vertices[end] = createNode(end);
        }
        addEdge(graph, vertices[start], vertices[end], weight);
    }
    printGraph(graph);
    printf("enter start node\n");
    int start;
    scanf("%d",&start);
    start--;
    vertices[start]->parent = 0;
    Dijkstra(graph, vertices[start], heap, 0, vertices);
    for(int i=0;i<n;i++)
    {
        printf("%d ",vertices[i]->p);
    }
    printf("\n");
    return 0;
}