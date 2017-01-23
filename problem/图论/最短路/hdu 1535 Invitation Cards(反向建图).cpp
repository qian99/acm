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
const int maxn=1000000+10;
struct Edge
{
    int v,w,next;
};
Edge edges[maxn<<1];
int head[maxn<<1],nEdge;
int d[maxn<<1],n,m;
bool vis[maxn<<1];
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void spfa()
{
    for(int i=1;i<=n*2;++i) d[i]=inf;
    d[1]=d[n+1]=0;
    queue<int>q;
    q.push(1);
    q.push(n+1);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        vis[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(d[v]>d[u]+edges[k].w)
            {
                d[v]=d[u]+edges[k].w;
                if(!vis[v]) {vis[v]=true;q.push(v);}
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        memset(head,0xff,sizeof(head));
        memset(vis,0,sizeof(vis));
        nEdge=-1;
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            AddEdge(v+n,u+n,w);
        }
        spfa();
        int ans=0;
        for(int i=1;i<=n*2;++i)
          ans+=d[i];
        printf("%d\n",ans);
    }
    return 0;
}
