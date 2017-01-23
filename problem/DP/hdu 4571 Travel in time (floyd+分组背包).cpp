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
const int maxt=300+10;
int dp[maxn][maxn][maxt],dis[maxn][maxn],vv[maxn],cc[maxn];
int n,m,S,E,T,N;
struct Node
{
    int val;
    vector<int>vt;
    bool operator <(const Node &a) const
    {
        return val<a.val;
    }
}node[maxn],nd[maxn];
void Init()
{
    for(int i=0;i<=n;++i)
        for(int j=0;j<=n;++j)
            dis[i][j]=(i==j)?0:inf;
    for(int i=0;i<maxn;++i)
        node[i].vt.clear();
}
void floyd()
{
    for(int k=0;k<n;++k)
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
}
void solve()
{
    memset(dp,0xff,sizeof(dp));
    for(int i=0;i<n;++i) if(dis[S][i]<=T) dp[0][i][dis[S][i]]=0;
    int u,v,size,t;
    for(int i=1;i<=N;++i)
    {
        for(u=0;u<n;++u)
            for(int j=0;j<=T;++j)
                dp[i][u][j]=dp[i-1][u][j];
        size=nd[i].vt.size();
        for(int k=0;k<size;++k)
        {
            v=nd[i].vt[k];
            for(int u=0;u<n;++u)
                for(int j=T;j>=0;--j)
                {
                    if(dp[i-1][u][j]==-1) continue;
                    t=j+dis[u][v]+cc[v];
                    if(t<=T)
                        dp[i][v][t]=max(dp[i][v][t],dp[i-1][u][j]+vv[v]);
                }
        }
    }
    for(u=0;u<n;++u)
        for(int i=0;i<=T;++i)
            if(i+dis[u][E]<=T)  dp[N][E][i+dis[u][E]]=max(dp[N][u][i],dp[N][E][i+dis[u][E]]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d%d%d%d%d",&n,&m,&T,&S,&E);
        Init();
        for(int i=0;i<n;++i)
            scanf("%d",&cc[i]);
        for(int i=0;i<n;++i)
        {
            scanf("%d",&vv[i]);
            node[i].val=vv[i];
            node[i].vt.push_back(i);
        }
        sort(node,node+n);
        N=1;
        nd[N]=node[0];
        int u,v,w;
        for(int i=1;i<n;++i)
        {
            v=node[i].vt[0];
            if(nd[N].val==node[i].val)
                nd[N].vt.push_back(v);
            else
            {
                nd[++N].vt.clear();
                nd[N].vt.push_back(v);
                nd[N].val=node[i].val;
            }
        }
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            dis[u][v]=dis[v][u]=min(dis[u][v],w);
        }
        floyd();
        solve();
        int ans=0;
        for(int i=0;i<=T;++i)
            ans=max(ans,dp[N][E][i]);
        printf("Case #%d:\n%d\n",tcase,ans);
    }
    return 0;
}
