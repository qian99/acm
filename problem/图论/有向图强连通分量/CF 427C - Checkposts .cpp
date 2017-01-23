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
const int mod=1000000007;
const int maxn=100000+10;
const int maxm=300000+10;
struct Edge
{
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxm<<1];
int head[maxn],pre[maxn],bccno[maxn],nEdge,dfs_clock,bcc_cnt;
int minv[maxn],cnt[maxn],val[maxn],n,m;
ll cost,ways;
stack<int>S;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
}
int tarjan(int u)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(!pre[v])
        {
            int lowv=tarjan(v);
            lowu=min(lowu,lowv);
        }
        else if(!bccno[v]&&pre[v]<lowu)
            lowu=pre[v];
    }
    if(lowu==pre[u])
    {
        bcc_cnt++;
        while(true)
        {
            int x=S.top();S.pop();
            bccno[x]=bcc_cnt;
            if(x==u) break;
        }
    }
    return lowu;
}
void solve()
{
    memset(pre,0,sizeof(pre));
    memset(bccno,0,sizeof(bccno));
    memset(minv,0x3f,sizeof(minv));
    dfs_clock=bcc_cnt=0;
    for(int i=1;i<=n;++i)
        if(!pre[i]) tarjan(i);
    for(int i=1;i<=n;++i)
    {
        int u=bccno[i];
        if(minv[u]>val[i])
        {
            minv[u]=val[i];
            cnt[u]=1;
        }
        else if(minv[u]==val[i])
            cnt[u]++;
    }
    cost=0;ways=1;
    for(int i=1;i<=bcc_cnt;++i)
    {
        cost+=minv[i];
        ways=ways*cnt[i]%mod;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=1;i<=n;++i)
            scanf("%d",&val[i]);
        scanf("%d",&m);
        int u,v;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        solve();
        printf("%I64d %I64d\n",cost,ways);
    }
    return 0;
}