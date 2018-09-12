#include "graph.h"
#include <iostream>

//打印出s到v的最短路径上的节点，应在BFS之后执行
void GraphPathPrint_helper(Graph *graph,int s,int v)
{
    if(v == s)
        std::cout << s << " ";
    else if(graph->G[v].pi == NIL)
        std::cout << "No Path Found!\n";
    else
    {
        GraphPathPrint_helper(graph,s,graph->G[v].pi);
        std::cout << v << " ";
    }
}

//打印出s到v的最短路径上的节点，应在BFS之后执行
void GraphPathPrint(Graph *graph,int s,int v)
{
    std::cout << "Path(" << s << "->" << v << "):";
    if(s<0 || v<0 || s > graph->nodeNum - 1 || v > graph->nodeNum - 1)
        std::cout << "s or d not in right range\n";
    GraphPathPrint_helper(graph,s,v);
    std::cout << "\n";
}