#include "graph.h"
#include <iostream>
#include <stdlib.h>//for malloc free

#define NODE_NUM 6//图中节点数量

int main()
{
    using namespace std;

    

    Graph *graph = GraphInit(NODE_NUM);

    GraphAddEdge(graph,0,1);

    GraphPrint(graph,GP_NEXT);

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
