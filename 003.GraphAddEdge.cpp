#include "graph.h"
#include <stdlib.h>

//在图中添加一条边，邻接链表表示的图
bool GraphAddEdge(Graph *graph,int s,int d)
{
    if(s<0 || d<0 || s > graph->nodeNum - 1 || d > graph->nodeNum - 1)
        return false;
    if(GraphHasEdge(graph,s,d))
        return false;
    LNode *lnptr=(LNode *)malloc(sizeof(LNode));
    lnptr->n = d;
    lnptr->next = graph->G[s].next;
    graph->G[s].next = lnptr;
    return true;
}