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
const int maxn=100000+10;
struct Edge
{
    int u,v,w;
};
vector<int>G[maxn];
vector<Edge>edges;
int d[maxn],dp[maxn][2];
int minval,minedges,S,T,maxstep,treelen;
int degree[maxn];
bool flag[maxn<<1];
void clearAll(int n)
{
    for(int i=0;i<=n;++i)
        G[i].clear();
    edges.clear();
    minedges=minval=inf;
    memset(flag,0,sizeof(flag));
    memset(d,0,sizeof(d));
    memset(dp,0,sizeof(dp));
    memset(degree,0,sizeof(degree));
}
void AddEdges(int u,int v,int w)
{
    edges.push_back((Edge){u,v,w});
    edges.push_back((Edge){v,u,w});
    degree[u]++;degree[v]++;
    int m=edges.size();
    G[u].push_back(m-2);
    G[v].push_back(m-1);
}
void dfs3(int u,int fa,int step)       //计算每个节点最长的两个分支
{
    int k;
    Edge e;
    d[u]=step;
    maxstep=max(maxstep,step);
    dp[u][0]=dp[u][1]=0;
    for(int i=0;i<G[u].size();++i)
    {
        k=G[u][i];
        e=edges[k];
        if(e.v==fa) continue;
        dfs3(e.v,u,step+1);
        int tmp=dp[e.v][0]+1;
        if(tmp>dp[u][0])
           dp[u][1]=dp[u][0],dp[u][0]=tmp;
        else if(tmp>dp[u][1])
           dp[u][1]=tmp;
    }
}
int dfs(int u,int fa,int mlen)   //遍历整个树并求结果
{
    int k,mlen2=0;
    Edge e;
    for(int i=0;i<G[u].size();++i)
    {
        k=G[u][i];
        e=edges[k];
        if(e.v==fa) continue;
        mlen=max(mlen,d[u]+dp[u][1]);     //从根节点到u的路径中遇到的最长路径长度
        mlen2=max(dfs(e.v,u,mlen),dp[e.v][0]+dp[e.v][1]);   //v点的子树中最长路径长度
    }
    int maxlen=0;
    for(int i=0;i<G[u].size();++i)
    {
        k=G[u][i];
        e=edges[k];
        if(e.v==fa) continue;
        maxlen=max(mlen2,mlen);   //选择mlen和mlen2的较大值
        if(maxlen*e.w<minval)
        {
            minval=maxlen*e.w;
            minedges=k;
        }
        else if(maxlen*e.w==minval)
            minedges=min(minedges,k);   //若相等，选择编号小的边
    }
    return mlen2;
}
int main()
{
    int size = 256 << 20; // 256MB
    char *p = (char*)malloc(size) + size;
    __asm__("movl %0, %%esp\n" :: "r"(p));
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    int n;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d",&n);
        clearAll(n);
        int a,b,c;
        for(int i=0;i<n-1;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            AddEdges(a,b,c);
        }
        maxstep=0;
        for(int i=1;i<=n;++i)
           if(degree[i]==1)
           {S=i;break;}
        dfs3(S,-1,0);
        treelen=maxstep;
        dfs(S,-1,0);
        printf("Case #%d: %d\n",tcase,minedges/2+1);
    }
    return 0;
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////



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
const int maxn=100000+10;
struct Edge
{
    int u,v,w;
};
vector<int>G[maxn];
vector<Edge>edges;
int d[maxn],dp[maxn][2];
int minval,minedges,S,T,maxstep,temp,treelen;
bool flag[maxn<<1];
void clearAll(int n)
{
    for(int i=0;i<=n;++i)
        G[i].clear();
    edges.clear();
    minedges=minval=inf;
    memset(flag,0,sizeof(flag));
    memset(d,0,sizeof(d));
    memset(dp,0,sizeof(dp));
}
void AddEdges(int u,int v,int w)
{
    edges.push_back((Edge){u,v,w});
    edges.push_back((Edge){v,u,w});
    int m=edges.size();
    G[u].push_back(m-2);
    G[v].push_back(m-1);
}
void dfs1(int u,int fa,int step)   //计算从某一点开始离这个点最远的点
{
    Edge e;
    if(step>maxstep)
       temp=u,maxstep=step;
    for(int i=0;i<G[u].size();++i)
    {
        e=edges[G[u][i]];
        if(e.v!=fa)
          dfs1(e.v,u,step+1);
    }
}
bool dfs2(int u,int fa,int step)   //计算每个点的深度并标记最长路上的边
{
    bool ff=false;
    Edge e;
    int k;
    d[u]=step;
    if(u==T) return true;
    for(int i=0;i<G[u].size();++i)
    {
        k=G[u][i];
        e=edges[k];
        if(e.v!=fa)
        {
            if(dfs2(e.v,u,step+1))
            {
                ff=true;
                flag[k]=flag[k^1]=true;
            }
        }
    }
    return ff;
}
void dfs3(int u,int fa)       //计算每个节点最长的两个分支
{
    int k;
    Edge e;
    dp[u][0]=dp[u][1]=0;
    for(int i=0;i<G[u].size();++i)
    {
        k=G[u][i];
        e=edges[k];
        if(e.v==fa) continue;
        dfs3(e.v,u);
        int tmp=dp[e.v][0]+1;
        if(tmp>dp[u][0])
           dp[u][1]=dp[u][0],dp[u][0]=tmp;
        else if(tmp>dp[u][1])
           dp[u][1]=tmp;
    }
}
int dfs(int u,int fa,int mlen)   //遍历整个树并求结果
{
    int k,mlen2=0;
    Edge e;
    for(int i=0;i<G[u].size();++i)
    {
        k=G[u][i];
        e=edges[k];
        if(e.v==fa) continue;
        mlen=max(mlen,d[u]+dp[u][1]);     //从根节点到u的路径中遇到的最长路径长度
        mlen2=max(dfs(e.v,u,mlen),dp[e.v][0]+dp[e.v][1]);   //v点的子树中最长路径长度
    }
    int maxlen=0;
    for(int i=0;i<G[u].size();++i)
    {
        k=G[u][i];
        e=edges[k];
        if(e.v==fa) continue;
        if(!flag[k]) maxlen=treelen;   //若不是最长路径上的边，则最长长度不变
        else maxlen=max(mlen2,mlen);   //否则选择mlen和mlen2的较大值
        if(maxlen*e.w<minval)
        {
            minval=maxlen*e.w;
            minedges=k;
        }
        else if(maxlen*e.w==minval)
            minedges=min(minedges,k);   //若相等，选择编号小的边
    }
    return mlen2;
}
int main()
{
    int size = 256 << 20; // 256MB
    char *p = (char*)malloc(size) + size;
    __asm__("movl %0, %%esp\n" :: "r"(p));
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    int n;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d",&n);
        clearAll(n);
        int a,b,c;
        for(int i=0;i<n-1;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            AddEdges(a,b,c);
        }
        maxstep=0;
        dfs1(1,-1,0);
        S=temp;
        maxstep=0;
        dfs1(S,-1,0);
        T=temp;
        dfs2(S,-1,0);
        treelen=d[T];
        dfs3(S,-1);
        dfs(S,-1,0);
        printf("Case #%d: %d\n",tcase,minedges/2+1);
    }
    return 0;
}
