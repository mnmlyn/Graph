#include "graph.h"
#include <stdlib.h>

//初始化邻接链表表示的图，初始化后为没有边相连的孤立节点图
Graph* GraphInit(int n)
{
    VNodeptr G = (VNodeptr)malloc(sizeof(VNode)*n);
    int i;
    for(i=0;i<n;++i)
    {
        G[i].n = i;
        G[i].color = WHITE;
        G[i].d = INFINITE;
        G[i].pi = NIL;
        G[i].next = NULL;
    }
    Graph * graph = (Graph *)malloc(sizeof(Graph));
    graph->G = G;
    graph->nodeNum = n;
}

//释放邻接链表表示的图的存储空间
void GraphDestroy(Graph *graph)
{
    //释放链表空间
    int i,n=graph->nodeNum;
    LNode *lnptr1,*lnptr2;
    for(i=0;i<n;++i)
    {
        lnptr1 = graph->G[i].next;
        while(lnptr1)
        {
            lnptr2 = lnptr1->next;
            free(lnptr1);
            lnptr1 = lnptr2;
        }
    }
    //释放数组空间
    free(graph->G);
    //释放Graph结构体空间
    free(graph);
}