#include "graph.h"
#include <iostream>
#include <stdlib.h>//for malloc free
#include <queue>//for BFS queue

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

    GraphDestroy(graph);


    cout << "End\n";
    cin.get();
    return 0;
}

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

//打印图，邻接链表表示的图
void GraphPrint(Graph *graph,int flags)
{
    using namespace std;
    int i,n=graph->nodeNum;
    VNodeptr G = graph->G;
    for(i=0;i<n;++i)
    {
        bool preArg = false;
        //node n
        cout << G[i].n;
        //color
        if(flags & GP_COLOR)
        {
            if(preArg)cout << ",";
            else
            {
                cout << "(";
                preArg = true;
            }
            switch(G[i].color)
            {
                case WHITE:
                    cout << "White";
                    break;
                case GRAY:
                    cout << "Gray";
                    break;
                case BLACK:
                    cout << "Black";
                    break;
                default:
                    cout << "Unknown";
                    break;
            }
        }
        //d
        if(flags & GP_D)
        {
            if(preArg)cout << ",";
            else
            {
                cout << "(";
                preArg = true;
            }
            cout << "d=";
            if(G[i].d == INFINITE)cout << "INFINITE";
            else cout << G[i].d;
        }
        //pi
        if(flags & GP_PI)
        {
            if(preArg)cout << ",";
            else
            {
                cout << "(";
                preArg = true;
            }
            cout << "pi=";
            if(G[i].pi == NIL)cout << "NIL";
            else cout << G[i].pi;
        }
        //)
        if(preArg)cout << ")";
        cout << endl;
        //next LNode
        if(flags & GP_NEXT)
        {
            cout << " -> ";
            LNode *lnptr=G[i].next;
            if(!lnptr)cout << "NULL";
            while(lnptr)
            {
                cout << lnptr->n << " ";
                lnptr = lnptr->next;
            }
            cout << endl;
        }
    }
}

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
