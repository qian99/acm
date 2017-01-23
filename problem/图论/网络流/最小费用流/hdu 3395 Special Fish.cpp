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
const int maxn=200+10;
const int maxm=100000+10;
struct Edge
{
    int to,cap,cost,next;
    Edge(){}
    Edge(int to,int cap,int cost,int next):to(to),cap(cap),cost(cost),next(next){}
}edges[maxm];
int head[maxn],d[maxn],p[maxn],nEdge;
bool inq[maxn];
void AddEdges(int from,int to,int cap,int cost)
{
    edges[++nEdge]=Edge(to,cap,cost,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(from,0,-cost,head[to]);
    head[to]=nEdge;
}
bool spfa(int s,int t,int &flow,int &cost)
{
    for(int i=0;i<=t;++i)
    {
        d[i]=inf;
        inq[i]=false;
    }
    queue<int>q;
    q.push(s);
    d[s]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(e.cap&&d[e.to]>d[u]+e.cost)
            {
                d[e.to]=d[u]+e.cost;
                p[e.to]=k;
                if(!inq[e.to]) {inq[e.to]=true;q.push(e.to);}
            }
        }
    }
    if(d[t]==inf) return false;
    if(d[t]>=0) return false;
    flow+=1;
    cost+=d[t];
    int u=t;
    while(u!=s)
    {
        edges[p[u]].cap-=1;
        edges[p[u]^1].cap+=1;
        u=edges[p[u]^1].to;
    }
    return true;
}
char att[maxn];
int val[maxn];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        if(n==0) break;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int S=0,T=2*n+1;
        for(int i=1;i<=n;++i)
            scanf("%d",&val[i]);
        for(int i=1;i<=n;++i)
        {
            AddEdges(S,i,1,0);
            AddEdges(i+n,T,1,0);
            scanf("%s",att+1);
            for(int j=1;j<=n;++j)
                if(att[j]=='1') AddEdges(i,j+n,1,-(val[i]^val[j]));
        }
        int flow=0,cost=0;
        while(spfa(S,T,flow,cost));
        printf("%d\n",-cost);
    }
    return 0;
}
