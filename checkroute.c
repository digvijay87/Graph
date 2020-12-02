#include<stdio.h>
#include<string.h>
#include<stdlib.h>
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

struct queue{
    int item[SIZE];
    int front;
    int rear;
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
/*
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
*/

struct queue * createqueue()
{
    struct queue *q = (struct queue*)malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}
void enqueue(struct queue* q, int v)
{
    if(q->rear == SIZE -1)
    {
        printf("queue is full\n");
    }
    else
    {
        if(q->front == -1)
            q->front++;
        q->rear++;
        q->item[q->rear] = v;

    }
}

int isempty(struct queue *q)
{
    if(q->rear == -1)
        return 1;
    else
        return 0;
}
int dequeue(struct queue *q)
{
    int ret;
    if(q->rear == -1){
        printf("Queue is empty\n");
        ret = -1;
    }
    else{
        ret = q->item[q->front];
        q->front++;
    }
    if(q->front > q->rear)
        q->front = q->rear = -1;
    return ret;
}
int checkroute(struct Graph *graph, int start, int end)
{
    struct queue * q = createqueue();
    int ret = 0;
    //mark vert as visited
    int arr[SIZE];
    int i = 0;
    graph->visited[start] = 1;
    enqueue(q,start);
    while(isempty(q) != 1)
    {
        int curvert = dequeue(q);
        //printf("Visited = %d\n",curvert);
        arr[i++] = curvert;
        if(curvert == end)
        {
          return 1;
        }
        struct node *temp = graph->adjlist[curvert];
        while(temp)
        {
            int adj = temp->dest;
           // printf("%d\n",adj);
            if(graph->visited[adj] == 0){
                graph->visited[adj] = 1;
            enqueue(q,adj);
            }
            temp = temp->next;
        }

    }
    printf("\n\n\n\nList of visited node in order\n");
    for(i=0;i<SIZE;i++){
        printf("%d\t",arr[i]);
    }
    printf("\n");
    return 0;
}
int main(void) {
    int ret = 0;
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
//    addedge(graph, 4,3);
    printgraph(graph);

    //dfs(graph, 0);
    ret = checkroute(graph,1,2);
    ret ? printf("route found\n") : printf("Route not found\n");

    return 0;
}
