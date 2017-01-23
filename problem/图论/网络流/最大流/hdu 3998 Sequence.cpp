#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=10000+10;
const int maxm=100000+10;
struct Edge
{
    int from,to,cap,flow,next;
    Edge(){};
    Edge(int ff,int tt,int cc,int fl,int nx){from=ff;to=tt;cap=cc;flow=fl;next=nx;}
}edges[maxm<<1];
int head[maxn],d[maxn],cur[maxn],nEdge;
bool vis[maxn];
void AddEdges(int from,int to,int cap)
{
    edges[++nEdge]=Edge(from,to,cap,0,head[from]);
    head[from]=nEdge;
    edges[++nEdge]=Edge(to,from,0,0,head[to]);
    head[to]=nEdge;
}
bool BFS(int s,int t)
{
    memset(vis,0,sizeof(vis));
    memset(d,0,sizeof(d));
    queue<int>q;
    q.push(s);vis[s]=true;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            Edge e=edges[k];
            if(!vis[e.to]&&e.cap>e.flow)
            {
                d[e.to]=d[u]+1;
                vis[e.to]=true;
                q.push(e.to);
            }
        }
    }
    return vis[t];
}
int DFS(int u,int a,int t)
{
    if(u==t||a==0) return a;
    int flow=0,f;
    for(int &k=cur[u];k!=-1;k=edges[k].next)
    {
        Edge e=edges[k];
        if(d[e.to]==d[u]+1&&(f=DFS(e.to,min(a,e.cap-e.flow),t))>0)
        {
            edges[k].flow+=f;
            edges[k^1].flow-=f;
            flow+=f;a-=f;
            if(a==0) break;
        }
    }
    return flow;
}
int Maxflow(int s,int t)
{
    int flow=0;
    while(BFS(s,t))
    {
        for(int i=0;i<=t;++i) cur[i]=head[i];
        flow+=DFS(s,inf,t);
    }
    return flow;
}
int num[maxn],dp[maxn];
int LIS(int n)
{
    int ans=0;
    for(int i=1;i<=n;++i)
    {
        dp[i]=1;
        for(int j=1;j<i;++j)
        {
            if(num[j]<num[i])
                dp[i]=max(dp[i],dp[j]+1);
        }
        ans=max(ans,dp[i]);
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=1;i<=n;++i)
            scanf("%d",&num[i]);
        int lis=LIS(n);
        int S=0,T=n*2+1;
        for(int i=1;i<=n;++i)
        {
            AddEdges(i,i+n,1);
            if(dp[i]==1) AddEdges(S,i,1);
            if(dp[i]==lis) AddEdges(i+n,T,1);
            for(int j=i+1;j<=n;++j)
            {
                if(dp[j]==dp[i]+1&&num[j]>num[i])
                    AddEdges(i+n,j,1);
            }
        }
        int ans=Maxflow(S,T);
        printf("%d\n",lis);
        printf("%d\n",ans);
    }
    return 0;
}

