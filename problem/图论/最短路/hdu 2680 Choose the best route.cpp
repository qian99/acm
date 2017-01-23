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
const int maxn=1000+10;
const int maxm=20000+10;
struct Edge
{
    int v,w,next;
};
Edge edges[maxm<<1];
int head[maxn],nEdge,n,m;
int d[maxn];
bool inq[maxn];
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
int spfa(int s,int t)
{
    for(int i=0;i<=n;++i) d[i]=inf;
    memset(inq,0,sizeof(inq));
    d[s]=0;inq[s]=true;
    queue<int>q;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(d[v]>d[u]+edges[k].w)
            {
                d[v]=d[u]+edges[k].w;
                if(!inq[v]) {inq[v]=true;q.push(v);}
            }
        }
    }
    return d[t]==inf?-1:d[t];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int s,t;
    while(~scanf("%d%d%d",&n,&m,&t))
    {
        s=0;
        int u,v,w;
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            //AddEdge(v,u,w);
        }
        int p;
        scanf("%d",&p);
        for(int i=0;i<p;++i)
        {
            scanf("%d",&v);
            AddEdge(s,v,0);
            //AddEdge(v,s,0);
        }
        int ans=spfa(s,t);
        printf("%d\n",ans);
    }
    return 0;
}
