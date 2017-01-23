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
ll d[15][1<<12],val[15];
ll g[15][15],n,m;
struct Node
{
    int u,st;
    Node(){}
    Node(int u,int st):u(u),st(st){}
};
void spfa(int S,int T)
{
    queue<Node>q;
    memset(d,0xff,sizeof(d));
    d[S][0]=0;
    q.push(Node(S,1<<S));
    Node node;
    while(!q.empty())
    {
        node=q.front();q.pop();
        int u=node.u;
        for(int i=0;i<n;++i)
        {
            if(i==u||g[u][i]==-1) continue;
            int state=node.st|(1<<i);
            if(d[i][state]==-1||d[i][state]>d[u][node.st]+g[u][i])
            {
                d[i][state]=d[u][node.st]+g[u][i];
                q.push(Node(i,state));
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    while(~scanf("%d%d%d",&n,&m,&t))
    {
        memset(g,0xff,sizeof(g));
        int u,v,S,T;
        ll w;
        scanf("%d%d",&S,&T);
        for(int i=0;i<n;++i)
            scanf("%lld",&val[i]);
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%lld",&u,&v,&w);
            if(g[u][v]==-1) g[u][v]=g[v][u]=w;
            else g[u][v]=g[v][u]=min(g[u][v],w);
        }
        spfa(S,T);
        ll ans=0;
        for(int i=0;i<(1<<n);++i)
        {
            ll v=0;
            if(d[T][i]==-1||d[T][i]>=t) continue;
            for(int j=0;j<n;++j)
                if(i&(1<<j)) v+=val[j];
            ans=max(v,ans);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
