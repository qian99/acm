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
const int maxn=2000+10;
const int maxm=maxn*maxn;
int pre[maxn];
int dfs_clock,n,m;
bool mz[maxn][maxn],flag[maxn][maxn];
void Init()
{
    memset(flag,0,sizeof(flag));
    memset(mz,0,sizeof(mz));
    memset(pre,0,sizeof(pre));
    dfs_clock=0;
}
void AddEdge(int u,int v,bool f)
{
    mz[u][v]=true;
    flag[u][v]=f;
}
int tarjan(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    for(int v=1;v<=n;++v)
    {
        if((!flag[u][v])||(v==fa)) continue;
        if(!pre[v])
        {
            int lowv=tarjan(v,u);
            lowu=min(lowu,lowv);
            if(lowv>pre[u])
            {
                printf("%d %d %d\n",u,v,2);
                flag[u][v]=flag[v][u]=false;
                continue;
            }
        }
        else if(pre[v]<lowu)
            lowu=pre[v];
    }
    return lowu;
}
int dfs(int u,int fa)
{
    int lowu=pre[u]=++dfs_clock;
    for(int v=1;v<=n;++v)
    {
        if((!flag[u][v])||(v==fa)) continue;
        if(!pre[v])
        {
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);
            if(flag[v][u])
            {
                if(lowv>pre[u])
                    {printf("%d %d %d\n",v,u,1);flag[u][v]=false;}
                else
                    {printf("%d %d %d\n",u,v,1);flag[v][u]=false;}
            }
        }
        else
        {
            if(flag[v][u])
                printf("%d %d %d\n",u,v,1);
            flag[u][v]=false;
            lowu=min(lowu,pre[v]);
        }
    }
    return lowu;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int u,v,type;
    scanf("%d%d",&n,&m);
    Init();
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d",&u,&v,&type);
        AddEdge(u,v,true);
        AddEdge(v,u,type==2);
    }
    tarjan(1,-1);
    memset(pre,0,sizeof(pre));
    dfs_clock=0;
    for(int i=1;i<=n;++i)
    {
        if(!pre[i])
            dfs(i,-1);
    }
    return 0;
}

