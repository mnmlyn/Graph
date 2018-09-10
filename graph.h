#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <limits.h>//for INT_MAX

//图的邻接链表表示法
//邻接链表中的链表节点
typedef struct LNode{
    int n;
    struct LNode *next;
} LNode;

//数组中的节点
typedef struct VNode{
    int n;
    int color;
    #define WHITE 0
    #define GRAY 1
    #define BLACK 2
    int d;
    #define INFINITE INT_MAX
    int pi;
    #define NIL -1
    LNode *next;
} VNode;
//图指针，不包含节点数
typedef VNode * VNodeptr;
//图指针，包含节点数
typedef struct Graph{
    VNodeptr G;
    int nodeNum;
} Graph;

//初始化邻接链表表示的图，初始化后为没有边相连的孤立节点图
Graph* GraphInit(int n);
//释放邻接链表表示的图的存储空间
void GraphDestroy(Graph *graph);
//判断一条边是否在图中，邻接链表表示的图
bool GraphHasEdge(Graph *graph,int s,int d);
//在图中添加一条边，邻接链表表示的图
bool GraphAddEdge(Graph *graph,int s,int d);
//打印图，邻接链表表示的图
void GraphPrint(Graph *graph,int flags);
#define GP_COLOR 1
#define GP_D 1<<1
#define GP_PI 1<<2
#define GP_NEXT 1<<3
/*
1(White,d=1,pi=2)
 -> 3 4 5 6
*/

#endif