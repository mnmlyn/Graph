#include "graph.h"
#include <iostream>
#include <stdlib.h>//for malloc free

#define NODE_NUM 6//图中节点数量

int main()
{
    using namespace std;
    Graph *graph = GraphInit(NODE_NUM);

    GraphAddEdge(graph,0,1);
    GraphAddEdge(graph,1,2);
    GraphAddEdge(graph,2,3);
    GraphAddEdge(graph,0,4);
    GraphAddEdge(graph,0,5);

    GraphPrint(graph,GP_NEXT);

    GraphBFS(graph,0);

    GraphPrint(graph,GP_NEXT | GP_COLOR | GP_D |GP_PI);

    GraphPathPrint(graph,1,3);

    GraphDFS(graph);

    GraphPrint(graph,GP_NEXT | GP_COLOR | GP_D | GP_F | GP_PI);

    GraphDestroy(graph);


    cout << "End\n";
    cin.get();
    return 0;
}