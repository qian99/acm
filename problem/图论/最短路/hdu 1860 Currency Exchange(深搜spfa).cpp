#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100+10;
struct Edge
{
    int v,w,next;
    double c,r;
};
Edge edges[maxn<<1];
int head[maxn],nEdge;
double d[maxn];
bool inq[maxn];
int n,m,s;
double V;
void AddEdge(int u,int v,double c,double r)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].c=c;
    edges[nEdge].r=r;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
bool spfa(int u)
{
    inq[u]=true;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(d[v]<(d[u]-edges[k].c)*edges[k].r)
        {
            d[v]=(d[u]-edges[k].c)*edges[k].r;
            if(!inq[v])
            {
                if(spfa(v)) return true;
            }
            else return true;
        }
    }
    inq[u]=false;
    return false;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d%lf",&n,&m,&s,&V))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v;
        double Rab,Cab,Rba,Cba;
        for(int i=1;i<=m;++i)
        {
            scanf("%d%d",&u,&v);
            scanf("%lf%lf%lf%lf",&Rab,&Cab,&Rba,&Cba);
            AddEdge(u,v,Cab,Rab);
            AddEdge(v,u,Cba,Rba);
        }
        memset(inq,0,sizeof(inq));
        memset(d,0,sizeof(d));
        d[s]=V;
        if(spfa(s)) puts("YES");
        else puts("NO");
    }
    return 0;
}
