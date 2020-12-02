#include<stdio.h>
#include<malloc.h>
//#include<stddef.h>
#define SIZE 5
/*
0 1 4
1 3 4
2 3
3
4 3
*/
/*
struct AdjNode{
    int dest;
    int visited;
    struct AdjNode *next;
};

struct AdjList{
    struct AdjNode *head;
};

struct Graph{
    int v;
    struct AdjList *arr;
};
struct AdjNode * newNode(int dest)
{
    struct AdjNode *node = (struct AdjNode*)malloc(sizeof(struct AdjNode));
    node->dest = dest;
    node->visited = 0;
    node->next = NULL;
    return node;
}
void addedge(struct Graph *graph, int src, int dest)
{
    struct AdjNode *node = newNode(dest);
    node->next = graph->arr[src].head;
    graph->arr[src].head = node;
    
    //node = newNode(src);
    //node->next = graph->arr[dest].head;
    //graph->arr[dest].head = node;
}

void printgraph(struct Graph* graph) 
{ 
    int v; 
    for (v = 0; v < graph->v; ++v) 
    { 
        struct AdjNode* pCrawl = graph->arr[v].head; 
        printf("\n Adjacency list of vertex %d\n %d ", v,v); 
        while (pCrawl) 
        { 
            printf("-> %d", pCrawl->dest); 
            pCrawl = pCrawl->next; 
        } 
        printf("\n"); 
    } 
} 
*/
struct node{
    int dest;
    struct node *next;
};
struct Graph{
    int v;
    int *visited;
    struct node **adjlist;
};

struct node* createNewnode(int dest)
{
    struct node * newNode = (struct node*)malloc(sizeof(struct node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

void addedge(struct Graph *graph, int src, int dest)
{
    struct node *newNode = createNewnode(dest);
    newNode->next = graph->adjlist[src];
    graph->adjlist[src] = newNode;
}

void printgraph(struct Graph* graph) 
{ 
    int v; 
    for (v = 0; v < graph->v; ++v) 
    { 
        struct node* pCrawl = graph->adjlist[v]; 
        printf("\n Adjacency list of vertex %d\n %d ", v,v); 
        while (pCrawl) 
        { 
            printf("-> %d", pCrawl->dest); 
            pCrawl = pCrawl->next; 
        } 
        printf("\n"); 
    } 
} 

void dfs(struct Graph *graph, int root)
{
    //int *arr;
    //arr = ()
    
    struct node *adjlist = graph->adjlist[root];
    struct node *temp = adjlist;
    graph->visited[root] = 1;
    printf("Visited = %d\n",root);
    while(temp != NULL)
    {
        int connected = temp->dest;
        if(graph->visited[connected] == 0)
        {
            dfs(graph, connected);
        }
        temp = temp->next;
    }
}

int main(void) {
    
    struct Graph *graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->v = SIZE;
    graph->adjlist = (struct node **)malloc(sizeof(struct node*) * SIZE);
    graph->visited = (int *)malloc(sizeof(int)*5);
    memset(graph->visited, 0, sizeof(int)*5);
    int i;
    for(i=0;i<SIZE;i++)
    {
        graph->adjlist[i] = NULL;
    }
    addedge(graph, 0 , 1);
    addedge(graph, 1, 4);
    addedge(graph, 0, 4);
    addedge(graph, 1, 3 );
    addedge(graph, 3,2);
    addedge(graph, 4,3);
    printgraph(graph);
    
    dfs(graph, 0);
    return 0;
}
