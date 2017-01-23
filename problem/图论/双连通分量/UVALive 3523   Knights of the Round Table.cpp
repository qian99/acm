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
const int maxn=1000+10;
struct Edge
{
    int u;
    int v;
};
int mz[maxn][maxn],color[maxn],bccno[maxn],ans[maxn],pre[maxn],dfs_clock,bcc_cnt;
vector<int>G[maxn],bcc[maxn];
stack<Edge>S;
void Init(int n,int m)
{
    for(int i=1;i<=n;++i)
    {
        G[i].clear();
        for(int j=1;j<=n;++j)
        {
            mz[i][j]=1;
        }
    }
    int a,b;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d",&a,&b);
        mz[a][b]=mz[b][a]=0;
    }
    for(int i=1;i<=n;++i)
    {
        for(int j=i+1;j<=n;++j)
        {
            if(mz[i][j])
            {
                G[i].push_back(j);
                G[j].push_back(i);
            }
        }
    }
}
int dfs(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    int sz=G[u].size();
    for(int i=0;i<sz;++i)
    {
        int v=G[u][i];
        Edge e=(Edge){u,v};
        if(!pre[v])
        {
            S.push(e);
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);
            if(lowv>=pre[u])
            {
                bcc_cnt++;bcc[bcc_cnt].clear();
                for(;;)
                {
                    Edge x=S.top();S.pop();
                    if(bccno[x.u]!=bcc_cnt) {bcc[bcc_cnt].push_back(x.u);bccno[x.u]=bcc_cnt;}
                    if(bccno[x.v]!=bcc_cnt) {bcc[bcc_cnt].push_back(x.v);bccno[x.v]=bcc_cnt;}
                    if(x.u==u&&x.v==v) break;
                }
            }
        }
        else if(pre[v]<pre[u]&&v!=fa)
        {
            S.push(e);
            lowu=min(lowu,pre[v]);
        }
    }
    return lowu;
}
void find_bcc(int n)
{
    memset(pre,0,sizeof(pre));
    memset(ans,0,sizeof(ans));
    memset(bccno,0,sizeof(bccno));
    dfs_clock=bcc_cnt=0;
    for(int i=1;i<=n;++i)
    {
        if(!pre[i]) dfs(i,-1);
    }
}
bool bipart(int u,int b)
{
   int sz=G[u].size();
   for(int i=0;i<sz;++i)
   {
       int v=G[u][i];
       if(bccno[v]!=b) continue;
       if(color[u]==color[v]) return false;
       if(!color[v])
       {
           color[v]=3-color[u];
           if(!bipart(v,b)) return false;
       }
   }
   return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int m,n;
    while(~scanf("%d%d",&n,&m))
    {
        if(n==0&&m==0) break;
        Init(n,m);
        find_bcc(n);
        for(int i=1;i<=bcc_cnt;++i)
        {
            int u=bcc[i][0];
            memset(color,0,sizeof(color));
            color[u]=1;
            if(!bipart(u,i))
            {
                for(int j=0;j<bcc[i].size();++j)
                   ans[bcc[i][j]]=1;
            }
        }
        int sum=0;
        for(int i=1;i<=n;++i)
        {
            if(!ans[i])
            sum++;
        }
        printf("%d\n",sum);
    }
    return 0;
}
