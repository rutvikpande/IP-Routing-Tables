/*
MIS: 111903076
DSA II
MiniProject
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "routingtab.h"

//Allocating Memory to Node structure
struct node* createnode(int v){
    struct node* newNode;
    if( (newNode= (struct node *)malloc(sizeof(struct node))) == NULL)
    {
        printf("\nError Occurred,Memory Not Allotted\n");
        exit(1);
    }
    newNode->vertex = v;
    newNode->next = NULL;
    newNode->head = NULL;
    return newNode;
}

//Allocating Memory to Graph structure
struct graph* creategraph(int vertices){
    struct graph* graph;
    if((graph= (struct graph *)malloc(sizeof(struct graph))) == NULL)
    {
        printf("\nError Occurred,Memory Not Allotted\n");
        exit(1);
    }
    graph->numOfVertices = vertices;

    if((graph->adjLists = (struct node **)malloc(vertices * sizeof(struct node*)))== NULL)
    {
        printf("\nError Occurred,Memory Not Allotted\n");
        exit(1);
    }

    if((graph->visited = (int *)malloc(vertices * sizeof(int)))== NULL)
    {
        printf("\nError Occurred,Memory Not Allotted\n");
        exit(1);
    }

    int i;
    for (i = 0; i < vertices; i++)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

 //Function for adding an edge
int addEdge(struct graph* graph, int src, int dest){
    //Generates adjacency matrix
    int i,j,V=graph->numOfVertices;
    int matrix[V][V];
    for(i=0;i<V;i++)
    {
        for(j=0;j<V;j++)
        {
            matrix[i][j]=0;
        }
    }

    for(i=0;i<V;i++)
    {
        struct node* p=graph->adjLists[i];
        while(p!=NULL)
        {
            matrix[i][p->vertex]=1;
            p=p->next;
        }
    }
    //Checking if edge exists
    if(matrix[src][dest]==1)
    {
        printf("Edge already exists!\n");
        return dest;
    }

    // Adding edge from source to destination
    struct node* newNode = createnode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Adding edge from destination to source
    newNode = createnode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
    return dest;
}

//Function for printing devices in each router
void getDevices(struct graph* graph){
    int v;
    printf("\n");
    printf("Router\tIPaddress\t\tSubmask\t\t\tInterface");
    for (v = 0; v < graph->numOfVertices; v++)
    {
        if(graph->adjLists[v]==NULL)
        {
            printf("\n%d\t", v);
            printf("No devices connected!");
            continue;
        }
        LinkedList *q = graph->adjLists[v]->head;
        if(q==NULL)
        {
            printf("\n%d\t", v);
            printf("No devices connected!");
        }
        int i=0;

        while(q!=NULL)
        {
            printf("\n%d\t%-20s\t%-20s\t%-20s", v,q->ip_address,q->submask,q->interface);
            q=q->next;
            i++;
        }
    }
}

//Function for comparing and returning minimum index
int findMinDistance(int dist[],bool markVertex[],int V){

    // Initializing minimum value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (markVertex[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

//Function for printing shortest path
void printRoute(int parent[], int j){

    // If j is source
    if (parent[j] == - 1)
        return;

    printRoute(parent, parent[j]);

    printf("%d ", j);
}

//Function for printing distance array
int printRouteTable(int dist[], int n, int parent[],int V){
    int src = 0;
    printf("Router\t\t Distance\tPath");
    for (int i = 1; i < V; i++)
    {
        if(dist[i]>=INT_MAX || dist[i]<=-INT_MAX+1)
        {

            printf("\n%d -> %d \t\t %d\t\t%d ", src, i, -1, src);
            printf("No Path exists!");
            continue;
        }
        printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src);
        printRoute(parent, i);
    }
    return 0;
}

//Function for implementing Dijkstra's algorithm
void dijkstrasAlgo(int V, int graph[V][V], int src){

    int dist[V];  //Storing the shortest distance from source to i
    bool markVertex[V]; //markVertex[i] is true if shortest path found
    int parent[V]; // Parent array to store shortest path tree

    // Initializing all distances as INFINITE and markVertex[] as false
    for (int i = 0; i < V; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        markVertex[i] = false;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Finding shortest path for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Picking the minimum distance to next node
        int u = findMinDistance(dist, markVertex, V);

        // Marking the picked vertex as processed
        markVertex[u] = true;

        // Updating distance value
        for (int v = 0; v < V; v++)
            if (!markVertex[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    // Printing the constructed distance array
    printRouteTable(dist, V, parent,V);
}

//Function for generating matrix and finding shortest path using Dijkstra's Algorithm
void shortestPaths(struct graph* graph,int V){
    int i,j;
    int matrix[V][V];
    for(i=0;i<V;i++)
    {
        for(j=0;j<V;j++)
        {
            matrix[i][j]=0;
        }
    }

    for(i=0;i<V;i++)
    {
        struct node* p=graph->adjLists[i];
        while(p!=NULL)
        {
            matrix[i][p->vertex]=1;
            p=p->next;
        }
    }
    dijkstrasAlgo(V, matrix, 0);
}


//Function for deleting an edge
void delEdge(struct graph* graph, int src, int dest){

    struct node* p;
    struct node* q;
    int flag=1;
    p=graph->adjLists[src];
    while(flag!=0)
    {
        if(p==NULL)
        {
            printf("Source Edge does not exist!\n");
            flag=0;
        }
        else if(graph->adjLists[src]->vertex==dest)
        {
            graph->adjLists[src]=p->next;
            free(p);
            flag=0;
        }
        else if(p->next!=NULL && p->next->vertex==dest)
        {
            q=p;
            p=p->next;
            q->next=p->next;
            free(p);
            flag=0;
        }
        else
        {
            q=p;
            p=p->next;
        }
    }
    p=graph->adjLists[dest];
    flag=1;

    while(flag!=0)
    {
        if(p==NULL)
        {
            printf("Destination Edge does not exist!\n");
            flag=0;
        }
        else if(graph->adjLists[dest]->vertex==src)
        {
            graph->adjLists[dest]=p->next;
            free(p);
            flag=0;
        }
        else if(p->next!=NULL && p->next->vertex==src)
        {
            q=p;
            p=p->next;
            q->next=p->next;
            free(p);
            flag=0;
        }
        else
        {
            q=p;
            p=p->next;
        }
    }
}


//Function for searching for a device with given IP address
void searchDevice(struct graph* graph, int vertex, char* ip){
    struct node* adjList = graph->adjLists[vertex];
    struct node* temp = adjList;
    if(temp==NULL)
    {
        printf("Initialize Nodes First!");
        return;
    }

    graph->visited[vertex] = 1;
    printf("Router %d - ", vertex);
    LinkedList *q=temp->head;
    int flag=0;

    while(q!=NULL)
    {
        if(strcmp(q->ip_address,ip)==0)
        {
            flag=1;
            break;
        }
        else
        {
            q=q->next;
        }
    }

    if(flag==1)
    {
        printf("Device Found!\n");
    }
    else
    {
        printf("Device NOT Found!\n");
    }

    while(temp!=NULL)
    {
        int connectedVertex = temp->vertex;

        if(graph->visited[connectedVertex] == 0)
        {
            searchDevice(graph, connectedVertex, ip);
        }
        temp = temp->next;
    }
}

//Function for reseting visited vertices
void resetVisited(struct graph* graph, int vertex){
    struct node* adjList = graph->adjLists[vertex];
    struct node* temp = adjList;

    graph->visited[vertex] = 0;

    while(temp!=NULL)
    {
        int connectedVertex = temp->vertex;

        if(graph->visited[connectedVertex] == 1)
        {
            resetVisited(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

//Function for initializing and adding device information
void addDeviceInfo(struct node*p){
    if(p==NULL)
    {
        printf("Add Router Node First!\n");
    }
    else if(p->head==NULL)
    {
        LinkedList *q;
        if( (q=(LinkedList *)malloc(sizeof(LinkedList))) == NULL)
        {
            printf("\n\nError Occurred,Memory Not Allotted\n\n");
            exit(1);
        }
        printf("/Device Details/\n");
        printf("Enter IP Address:");
        scanf("%s",q->ip_address);
        printf("Enter Submask:");
        scanf("%s", q->submask);
        printf("Enter Interface:");
        scanf("%s",q->interface);
        q->next=NULL;
        p->head=q;
    }
    else
    {
        LinkedList *r=p->head;
        while(r->next!=NULL)
        {
            r=r->next;
        }
        LinkedList *q;
        if( (q=(LinkedList *)malloc(sizeof(LinkedList))) == NULL)
        {
            printf("\n\nError Occurred,Memory Not Allotted\n\n");
            exit(1);
        }
        printf("/Device Details/\n");
        printf("Enter IP Address:");
        scanf("%s",q->ip_address);
        printf("Enter Submask:");
        scanf("%s",q->submask);
        printf("Enter Interface:");
        scanf("%s",q->interface);
        q->next=NULL;
        r->next=q;
    }

}

//Function for printing device information
void printDeviceInfo(struct node* p){
    if(p==NULL)
    {
        printf("Node does not exist!\n");
        return;
    }
    LinkedList *q=p->head;
    int i=0;
    if(q==NULL)
    {
        printf("No Devices connected!");
    }
    while(q!=NULL)
    {
        printf("Device %d\n",i);
        printf("IP Address: %s \n",q->ip_address);
        printf("Submask: %s \n",q->submask);
        printf("Interface: %s \n",q->interface);
        q=q->next;
        i++;
        printf("\n");
    }
}

//Function for printing graph
void printGraph(struct graph* graph){
    int v;
    for (v = 0; v < graph->numOfVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        printf("\nAdjacency List of Routers connected to Router %d => ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL");
    }
}

