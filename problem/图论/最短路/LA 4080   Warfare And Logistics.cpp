#include <iostream>
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
typedef long long LL;
const int maxn=500+10;
const int maxm=3000+10;
int n,m,l;
struct Edge
{
    int from,to,dist;
};
struct HeapNode
{
    int d,u,pos;
    bool operator < (const HeapNode a) const
    {
        return d>a.d;
    }
};
vector<Edge>edges;
vector<int>G[maxn];
bool vis[maxn],hash[maxm];
int dis[maxn],p[maxn];
LL sum[maxm][maxn],ss[maxn];
void Init()
{
    for(int i=0;i<=n;++i) G[i].clear();
    edges.clear();
}
void addEdges(int from,int to,int dist)
{
    edges.push_back((Edge){from,to,dist});
    int temp=edges.size();
    G[from].push_back(temp-1);
}
LL dijkstra(int s,int k)
{
    priority_queue<HeapNode>q;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;++i)
       dis[i]=l;
    dis[s]=0;
    q.push((HeapNode){0,s,-1});
    while(!q.empty())
    {
        HeapNode hp=q.top();q.pop();
        int u=hp.u;
        if(vis[u]) continue;
        vis[u]=true;
        if(k==-1&&hp.u!=s)
          hash[hp.pos]=hash[hp.pos^1]=true;
        for(int i=0;i<G[u].size();++i)
        {
            int v=G[u][i];
            if(k==v||((k^1)==v)) continue;
            Edge x=edges[v];
            if(dis[u]+x.dist<dis[x.to])
            {
                dis[x.to]=dis[u]+x.dist;
                q.push((HeapNode){dis[x.to],x.to,v});
            }
        }
    }
    LL ans=0;
    for(int i=1;i<=n;++i)
      ans+=dis[i];
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    //int tcase=0;
    while(~scanf("%d%d%d",&n,&m,&l))
    {
        //if(tcase++) printf("\n");
        Init();
        int a,b,c;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            addEdges(a,b,c);
            addEdges(b,a,c);
        }
        LL ans1=0,ans2=0;
        memset(sum,0,sizeof(sum));
        memset(ss,0,sizeof(ss));
        for(int i=1;i<=n;++i)
        {
            memset(hash,0,sizeof(hash));
            ss[i]=dijkstra(i,-1);
            for(int j=0;j<m*2;++j)
            {
                if(!hash[j]) sum[j][i]=ss[i];
                else sum[j][i]=dijkstra(i,j);
            }
        }
        for(int j=0;j<m*2;++j)
        {
            LL all=0;
            for(int i=1;i<=n;++i)
               all+=sum[j][i];
            ans2=max(ans2,all);
        }
        for(int i=1;i<=n;++i)
           ans1+=ss[i];
        printf("%lld %lld\n",ans1,ans2);
    }
    return 0;
}
