#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=3000+100;
const int maxm=50000+10;
struct Edge
{
    int to,cap,cost,next;
//    Edge(){}
//    Edge(int to,int cap,int cost,int next):to(to),cap(cap),cost(cost),next(next){}
};
int head[maxn],d[maxn],p[maxn];
int S,T,nEdge,Cost,Flow,n,m;
bool inq[maxn];
Edge edges[maxm<<1];
int q[maxn];
void AddEdges(int from,int to,int cap,int cost)
{
    edges[++nEdge].to=to;
    edges[nEdge].cap=cap;
    edges[nEdge].cost=cost;
    edges[nEdge].next=head[from];
    head[from]=nEdge;

    edges[++nEdge].to=from;
    edges[nEdge].cap=0;
    edges[nEdge].cost=-cost;
    edges[nEdge].next=head[to];
    head[to]=nEdge;
//        edges[++nEdge]=Edge(from,to,cap,cost,head[from]);
//        head[from]=nEdge;
//        edges[++nEdge]=Edge(to,from,0,-cost,head[to]);
//        head[to]=nEdge;
}
bool spfa()
{
    for(int i=0;i<=2*n+2;++i)
    {
        inq[i]=false;
        d[i]=inf;
    }
//    memset(inq,0,sizeof(inq));
    d[S]=0;p[S]=0;
    int start=0,fail=1;
    q[0]=S;
    while(start!=fail)
    {
        int u=q[start++];

        for(int k=head[u];k;k=edges[k].next)
        {
            Edge e=edges[k];
            if(e.cap&&d[e.to]>d[u]+e.cost)
            {
                d[e.to]=d[u]+e.cost;
                p[e.to]=k;
                if(!inq[e.to])
                {
                    inq[e.to]=true;
                    q[fail++]=e.to;
                    if(fail==maxn) fail=0;
                }
            }
        }
        if(start==maxn) start=0;
        inq[u]=false;
    }
    if(d[T]==inf) return false;
//    int a=1;
    int u=T;
//    while(u!=S)
//    {
//        a=min(a,edges[p[u]].cap);
//        u=edges[p[u]^1].to;
//    }
    Flow+=1;
    Cost+=d[T];
    u=T;
    int pp;
    while(u!=S)
    {
        pp=p[u];
        edges[pp].cap-=1;
        edges[pp^1].cap+=1;
        u=edges[pp^1].to;
    }
    return true;
}
inline void reads(int & x)
{
    char c;
    bool neg=false;
    while(((c=getchar())<'0'||c>'9')&&c!='-');
    if(c=='-')
    {
        neg=true;
        while((c=getchar())<'0'||c>'9');
    }
    x=c-'0';
    while(c=getchar(),c>='0'&&c<='9') x=x*10+c-'0';
    if(neg) x=-x;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        reads(n);reads(m);
//        scanf("%d%d",&n,&m);
        printf("Case %d: ",++tcase);
        int u,v,w;
        S=0,T=2*n+1;
        memset(head,0,sizeof(head));
        nEdge=1;
        for(int i=0;i<m;++i)
        {
            reads(u);reads(v);reads(w);
//            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u,v+n,1,w);
            AddEdges(v,u+n,1,w);
        }
        for(int i=1;i<=n;++i)
        {
            AddEdges(S,i,1,0);
            AddEdges(i+n,T,1,0);
        }
        Flow=Cost=0;
        while(spfa());
        if(Flow!=n)
            printf("NO\n");
        else printf("%d\n",Cost);
    }
    return 0;
}
