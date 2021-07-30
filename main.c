/*
MIS: 111903076
DSA II
MiniProject
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "routingtab.h"

int main(){
    printf("Routing Tables:\n\n");

    printf("Enter Maximum no of Routers to be added:");
    int V; //Taking input of Max no of Vertices to be included
    scanf(" %d",&V);
    if(V==0)
    {
        printf("Graph cannot be created! Exit Successful!");
        exit(0);
    }

    //General Instructions
    printf("Routers are marked from 0 to %d\n",V-1);
    printf("Root Node starts at 0 ");

    //Initializing Graph
    struct graph* graph = creategraph(V);

    char ch; //For taking choice

    int root=0; //Storing last known Root

    while(ch!='8')
    {
        printf("\n");
        printf("\nOptions:\n");
        printf("1.Add an Edge \n");
        printf("2.Delete an Edge \n");
        printf("3.Calculate Routes from Root Node 0 \n");
        printf("4.Print Router Connections and Routing Table \n");
        printf("5.Add Device \n");
        printf("6.Print Devices \n");
        printf("7.Search Device \n");
        printf("8.Exit \n");


        printf("$>");
        scanf(" %c",&ch);

        int s,d; //Source, Destination Edges
        int y; //Stores Router Node Vertex
        char ip[15]; //Stores Device IP Address
        switch(ch)
        {
            case '1':
                printf("Add an Edge:\n");
                printf("Enter Nodes with a space in between:");
                scanf("%d %d",&s,&d);
                if(s<V && d<V)
                {

                    if(s==d)
                    {
                        printf("Self referential edges can't be inserted.");
                    }
                    else
                    {
                        root = addEdge(graph, s, d);
                    }
                }
                else
                {
                    printf("Enter node within limits!");
                }

                break;
            case '2':
                printf("Delete an Edge:\n");
                printf("Enter Nodes with a space in between:");
                scanf("%d %d",&s,&d);
                if(s<V && d<V)
                {

                    if(s==d)
                    {
                        printf("Self referential edges can't be inserted.");
                    }
                    else
                    {
                        delEdge(graph, s, d);
                        if(s==root || d==root)
                        {
                            root=0;
                        }
                    }
                }
                else
                {
                    printf("Enter nodes within limits!");
                }
                break;
            case '3':
                printf("Shortest Routes from Root Node 0:\n");
                shortestPaths(graph,V);
                break;
            case '4':
                printf("//Router Connections//");
                printGraph(graph);
                printf("\n\n//Routing Table//");
                getDevices(graph);
                break;
            case '5':
                printf("Add Device:\n");
                printf("Enter Router Node on which device needs to be inserted:");
                scanf("%d",&y);
                if(y>=V)
                {
                    printf("Invalid Node!");
                    break;
                }
                addDeviceInfo(graph->adjLists[y]);
                break;
            case '6':
                printf("Print Devices:\n");
                printf("Enter Router Node whose devices needs to printed:");
                scanf("%d",&y);
                if(y>=V)
                {
                    printf("Invalid Node!");
                    break;
                }
                printDeviceInfo(graph->adjLists[y]);
                break;
            case '7':
                printf("Search Device:\n");
                printf("Enter IP Address of Device:");
                scanf("%s",&ip);
                searchDevice(graph,root,ip); //Search for Device in each node
                resetVisited(graph,root); //To reset visited flags on each node
                break;
            case '8':
                printf("Exit successful!");
                break;
            default:
                printf("Invalid Option!");
                break;

        }

    }

    return 0;
}
