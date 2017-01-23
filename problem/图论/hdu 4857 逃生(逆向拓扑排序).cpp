#include<cstdio>
#include<iostream>
#include<string>
#include<cmath>
#include<queue>
#include<cstring>
#include<algorithm>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL;
using namespace std;
const int maxn=30000+10;
const int maxm=100000+10;
struct Edge
{
    int v,next;
    Edge(int v=0,int next=0):v(v),next(next){}
}edges[maxm];
int head[maxn],degree[maxn],nEdge;
int ans[maxn];
int n,m,tot;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
}
void solve()
{
    priority_queue<int>q;
    for(int i=1;i<=n;++i)
        if(degree[i]==0) q.push(i);
    tot=n;
    while(!q.empty())
    {
        int u=q.top();q.pop();
        ans[--tot]=u;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            degree[v]--;
            if(degree[v]==0)
                q.push(v);
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
        memset(degree,0,sizeof(degree));
        nEdge=-1;
        int u,v;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(v,u);
            degree[u]++;
        }
        solve();
        for(int i=0;i<n;++i)
        {
            if(i) printf(" ");
            printf("%d",ans[i]);
        }
        printf("\n");
    }
    return 0;
}
