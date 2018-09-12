#include "graph.h"
#include <iostream>
#include <queue>//for BFS queue

//广度优先搜索
void GraphBFS(Graph *graph,int s)
{
    //args init
    int i,n=graph->nodeNum,u,v;
    for(i=0;i<n;++i)
    {
        graph->G[i].color = WHITE;
        graph->G[i].d = INFINITE;
        graph->G[i].pi = NIL;
    }
    //循环不变式：队列Q中存储着访问到却还没有遍历其邻接链表的节点
    //访问源点s
    graph->G[s].color = GRAY;
    std::cout << "find: " << s << " ";
    graph->G[s].d = 0;
    graph->G[s].pi = NIL;
    std::queue<int> Q;
    Q.push(s);
    while(!Q.empty())
    {
        u = Q.front();
        Q.pop();
        //访问节点u的所有相邻白色节点
        LNode *lnptr = graph->G[u].next;
        while(lnptr)
        {
            v = lnptr->n;
            if(graph->G[v].color == WHITE)
            {
                graph->G[v].color = GRAY;
                std::cout << v << " ";
                graph->G[v].d = graph->G[u].d + 1;
                graph->G[v].pi = u;
                Q.push(v);
            }
            lnptr = lnptr->next;
        }
        graph->G[u].color = BLACK;
    }
    std::cout << "\n";
}