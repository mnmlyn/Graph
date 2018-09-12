#include "graph.h"

//判断一条边是否在图中，邻接链表表示的图
bool GraphHasEdge(Graph *graph,int s,int d)
{
    if(s<0 || d<0 || s > graph->nodeNum - 1 || d > graph->nodeNum - 1)
        return false;
    LNode *lnptr=graph->G[s].next;
    while(lnptr)
    {
        if(lnptr->n == d)return true;
        lnptr = lnptr->next;
    }
    return false;
}