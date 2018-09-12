#include "graph.h"

//深度优先搜索，辅助递归函数
void GraphDFS_helper(Graph *graph,int u,int &time)
{
    graph->G[u].d = ++time;
    graph->G[u].color = GRAY;
    LNode *lnptr = graph->G[u].next;
    while(lnptr)
    {
        int v = lnptr->n;
        if(graph->G[v].color == WHITE)
        {
            graph->G[v].pi = u;
            GraphDFS_helper(graph,v,time);
        }
        lnptr = lnptr->next;
    }
    graph->G[u].color = BLACK;
    graph->G[u].f = ++time;
}

//深度优先搜索
void GraphDFS(Graph *graph)
{
    int i,n=graph->nodeNum,time=0;
    //init args
    for(i=0;i<n;++i)
    {
        graph->G[i].color = WHITE;
        graph->G[i].pi = NIL;
    }
    //DFS
    for(i=0;i<n;++i)
    {
        if(graph->G[i].color == WHITE)
            GraphDFS_helper(graph,i,time);
    }
}