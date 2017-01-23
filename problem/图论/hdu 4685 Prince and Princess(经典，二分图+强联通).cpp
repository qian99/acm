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
typedef long long ll;
const int maxn=4000+10;
vector<int>G[maxn],res[maxn];
stack<int>S;
int link[maxn],linkp[maxn],pre[maxn],sccno[maxn];
int M,N,scc_cnt,dfs_clock,m,n;
bool vis[maxn];
void clearAll()
{
    for(int i=0;i<=N*4;++i)
    {
        G[i].clear();
        res[i].clear();
    }
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    scc_cnt=dfs_clock=0;
}
bool dfs(int u)
{
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!vis[v])
        {
            vis[v]=true;
            if(link[v]==-1||dfs(link[v]))
            {
                link[v]=u;
                linkp[u]=v;
                return true;
            }
        }
    }
    return false;
}
void hungary()
{
    memset(link,0xff,sizeof(link));
    memset(linkp,0xff,sizeof(linkp));
    for(int i=1;i<=N;++i)
    {
        memset(vis,0,sizeof(vis));
        dfs(i);
    }
}
void build()
{
    int k;
    M=2*N;
    for(int i=1;i<=n;++i)
    {
        if(linkp[i]==-1)
        {
            linkp[i]=++M;
            for(int j=1;j<=N;++j)
               G[j].push_back(M);
        }
        G[linkp[i]].push_back(i);
    }
    for(int i=1;i<=m;++i)
    {
        if(link[i+N]==-1)
        {
            link[i+N]=++M;
            for(int j=1;j<=N;++j)
              G[M].push_back(j+N);
        }
        G[i+N].push_back(link[i+N]);
    }
}
int tarjan(int u)
{
    int lowu=pre[u]=++dfs_clock;
    S.push(u);
    for(int i=0;i<G[u].size();++i)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            int lowv=tarjan(v);
            lowu=min(lowu,lowv);
        }
        else if(!sccno[v])
            lowu=min(lowu,pre[v]);
    }
    if(lowu==pre[u])
    {
        scc_cnt++;
        while(true)
        {
            int x=S.top();S.pop();
            sccno[x]=scc_cnt;
            if(x==u) break;
        }
    }
    return lowu;
}
void slove()
{
    hungary();
    build();
    for(int i=1;i<=M;++i)
       if(!pre[i]) tarjan(i);
    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<G[i].size();++j)
        {
            int x=G[i][j];
            if(x>N+m) continue;
            if(sccno[i]==sccno[x])
              res[i].push_back(x-N);
        }
    }
    for(int i=1;i<=n;++i)
    {
        sort(res[i].begin(),res[i].end());
        int sz=res[i].size();
        printf("%d",sz);
        for(int j=0;j<sz;++j)
            printf(" %d",res[i][j]);
        printf("\n");
    }
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
        scanf("%d%d",&n,&m);
        N=max(n,m);
        clearAll();
        int k,p;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&k);
            for(int j=0;j<k;++j)
            {
                scanf("%d",&p);
                G[i].push_back(p+N);
            }
        }
        printf("Case #%d:\n",tcase);
        slove();
    }
    return 0;
}
