#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int t = 1;
int edgeIndex=0;

struct Edge{
    int start;
    int weight;
    int end;
};

int merge(struct Edge* arr[],int i, int k, int j)
{
    int left = i, right = k+1;
    struct Edge* B[100];
    int p=i;
    while(left<k+1 && right<j+1)
    {
        if(arr[left]->weight<arr[right]->weight)
        {
            B[p++] = arr[left++];
        }
        else
        {
            B[p++] = arr[right++];  
        }
    }
    while(left<=k)
    {
        B[p++] = arr[left++];
    } 
    while(right<=j)
    {
        B[p++] = arr[right++];
    }
    for(int n=i;n<=j;n++) arr[n] = B[n];
    return 0;
}

int mergeSort(struct Edge* arr[],int i,int j)
{
    if(i==j) return 0;
    int k = (i+j)/2;
    mergeSort(arr,i,k);
    mergeSort(arr,k+1,j);
    merge(arr,i,k,j);
    return 0;
}
 
struct node
{
    int vertex;
    int d;
    int f;
    struct node* next;
    struct node* parent;
};

struct node* createNode(int v)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph
{
    int numVertices;
    struct node** adjLists;
    int** weightLists;
    char** color; 
    int numEdges;
    int* C;
    int* S;
    int** L;
    struct Edge** edges; 
};

void addEdge(struct Graph* graph, struct node* src, struct node* dest, int weight)
{
    struct Edge* e = malloc(sizeof(struct Edge));
    e->start = src->vertex;
    e->end = dest->vertex;
    e->weight = weight;
    graph->edges[edgeIndex++] = e;
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

struct Graph* createGraph(int vertices, int edges)
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

    graph->color = (char**)malloc(vertices*sizeof(char));
    for(int i=0;i<=vertices;i++)
    {
        graph->color[i] = (char*)malloc(7*sizeof(char));
        graph->color[i] = "red";
    }
    graph->numEdges = edges;
    
    graph->C = (int*)malloc(vertices*sizeof(int));
    for(int i=0;i<vertices;i++) graph->C[i] = i;

    graph->S = (int*)malloc(vertices*sizeof(int));
    for(int i=0;i<vertices;i++) graph->S[i] = 1;

    graph->L = (int**)malloc(vertices*sizeof(int*));
    for(int i=0;i<vertices;i++)
    {
        graph->L[i] = malloc(vertices*sizeof(int));
        for(int j=0;j<vertices;j++)
        {
            graph->L[i][j] = 0;
        }
    }
    graph->edges = (struct Edge**)malloc(edges*sizeof(struct Edge*));

    return graph;
}

struct Graph* Krushkals(struct Graph* graph, struct node* vertices[])
{
    struct Graph* MST = createGraph(graph->numVertices,graph->numEdges-1);
    mergeSort(graph->edges, 0,graph->numEdges-1);
    for(int i=0;i<graph->numEdges;i++)
    {
        struct Edge* e = graph->edges[i];
        int color1 = graph->C[e->start];
        int color2 = graph->C[e->end];
        if(color1 != color2)
        {
            addEdge(MST,vertices[e->start],vertices[e->end],graph->weightLists[e->start][e->end]);
            if(graph->S[color1] > graph->S[color2])
            {
                graph->C[e->end] = color1;
                for(int i=0;i<graph->numVertices;i++)
                {
                    if(graph->L[color2][i] != 0)
                    {
                        graph->L[color1][i] = 1;
                        graph->L[color2][i] = 0;
                        graph->C[i] = color1;
                    } 
                }
                graph->S[color1] += graph->S[color2];
                graph->S[color2] = 0;
            }
            else{
                graph->C[e->start] = color2;
                for(int i=0;i<graph->numVertices;i++)
                {
                    if(graph->L[color1][i] != 0)
                    {
                        graph->L[color2][i] = 1;
                        graph->L[color1][i] = 0;
                        graph->C[i] = color2;
                    } 
                }
                graph->S[color2] += graph->S[color1];
                graph->S[color1] = 0;
            }
        }
    }
    return MST;
}

int printPath(int v, struct node* vertices[])
{
    if(vertices[v]->parent->vertex == v) printf("%d\n",v+1);
    else {
        printPath(vertices[v]->parent->vertex, vertices);
        printf("%d\n",v+1);
    }
    return 0;
}

void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v + 1);
        while (temp)
        {
            printf("%d -> ", temp->vertex + 1);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main()
{
    printf("enter num of nodes\n");
    int n;
    scanf("%d",&n);
    struct node* vertices[n+1];
    for(int i=0;i<=n;i++) vertices[i] = 0;
    printf("enter num of edges\n");
    int edges;
    scanf("%d",&edges);
    struct Graph* graph = createGraph(n+1,edges);
    printf("enter the edges\n");
    while(edges--)
    {
        int start, end, weight;
        scanf("%d %d %d",&start,&end, &weight);
        start--;
        end--;
        if(!vertices[start]) vertices[start] = createNode(start);
        if(!vertices[end]) vertices[end] = createNode(end);
        addEdge(graph, vertices[start], vertices[end], weight);
    }
    struct Graph* MST = Krushkals(graph, vertices );
    printGraph(MST);
    return 0;
}
