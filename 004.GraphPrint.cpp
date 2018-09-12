#include "graph.h"
#include <iostream>

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
        //f
        if(flags & GP_F)
        {
            if(preArg)cout << ",";
            else
            {
                cout << "(";
                preArg = true;
            }
            cout << "f=";
            if(G[i].f == INFINITE)cout << "INFINITE";
            else cout << G[i].f;
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