/*
MIS: 111903076
DSA II
MiniProject
*/
#ifndef ROUTINGTAB_H_INCLUDED
#define ROUTINGTAB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

//Device Structure
typedef struct LinkedList{
    char ip_address[20]; //For storing IP Address
    char submask[20]; //For storing submask
    char interface[10]; //For storing interface
    struct LinkedList *next; //Pointer to the next device
}LinkedList;

//Router Node Structure
struct node{
    int vertex; //For storing vertex number
    struct node* next; //Pointer to next router
    LinkedList *head; //Pointer for pointing at the start of the linked list of devices
};

//Structure for Network of routers
struct graph{
    int numOfVertices; //Max no of vertices(routers) to be included
    int* visited; //For marking vertices that are visited
    struct node** adjLists; //For storing an array of Linked lists
};

//Function Declarations
struct graph* creategraph(int); //Allocating memory to graph structure
struct node* createnode(int); //Allocating memory to node structure
int addEdge(struct graph*, int, int); //Adding an edge
void delEdge(struct graph*, int, int); //Deleting an edge
void printGraph(struct graph*); //Printing graph
void searchDevice(struct graph*, int, char*); //Searching for a device with given IP address
void resetVisited(struct graph*, int); //Resetting visited vertices
void shortestPaths(struct graph*,int); //Generating matrix and finding shortest path using Dijkstra's Algorithm
void dijkstrasAlgo(int V, int[][V], int); //Dijkstra's algorithm
int findMinDistance(int [],bool [],int); //Comparing and returning Minimum Index
void printRoute(int [], int); //Printing shortest path
int printRouteTable(int [], int, int [],int); //Printing shortest paths to all vertices along with distances
void addDeviceInfo(struct node*); //Initializing and adding device to router
void printDeviceInfo(struct node*); //Printing devices connected on a specific router
void getDevices(); //Printing devices connected on each router

#endif // ROUTINGTAB_H_INCLUDED
