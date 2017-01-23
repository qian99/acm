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
using namespace std;
const int maxn=2000+10;
const int maxm=10000+10;
struct Edge
{
    int v,next;
};
Edge edges[maxm],ee[maxm];
int head[maxn],hh[maxn],nEdge,ecnt;
int pre[maxn],sccno[maxn],scc_cnt,dfs_clock,n;
int w[maxn],val[maxn],dp[maxn],trans[maxn],a,b;
char sq[50][50];
stack<int>S;
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(hh,0xff,sizeof(hh));
    memset(pre,0,sizeof(pre));
    memset(sccno,0,sizeof(sccno));
    memset(val,0,sizeof(val));
    nEdge=ecnt=-1;
    scc_cnt=dfs_clock=0;
}
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void addedge(int u,int v)
{
    ecnt++;
    ee[ecnt].v=v;
    ee[ecnt].next=hh[u];
    hh[u]=ecnt;
}
inline bool check(int x,int y)
{
    return x>=0&&y>=0&&x<a&&y<b&&sq[x][y]!='#';
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
void dfs(int u)
{
    dp[u]=val[u];
    int tmp=0;
    for(int k=hh[u];k!=-1;k=ee[k].next)
    {
        int v=ee[k].v;
        dfs(v);
        tmp=max(tmp,dp[v]);
    }
    dp[u]+=tmp;
}
int solve()
{
    for(int i=0;i<n;++i)
     if(!pre[i]) tarjan(i);
    int u,v;
    for(u=0;u<n;++u)
    {
        val[sccno[u]]+=w[u];
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            v=edges[k].v;
            if(sccno[u]!=sccno[v])
              addedge(sccno[u],sccno[v]);
        }
    }
    dfs(sccno[0]);
    return dp[sccno[0]];
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int x,y;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&a,&b);
        n=a*b;
        Init();
        int tnt=0;
        for(int i=0;i<a;++i)
          scanf("%s",sq[i]);
        for(int i=0;i<a;++i)
          for(int j=0;j<b;++j)
          {
              if(sq[i][j]>='0'&&sq[i][j]<='9')
                w[i*b+j]=(int)(sq[i][j]-'0');
              else w[i*b+j]=0;
              if(sq[i][j]=='#') continue;
              x=i+1;y=j;
              if(check(x,y)) AddEdge(i*b+j,x*b+y);
              x=i;y=j+1;
              if(check(x,y)) AddEdge(i*b+j,x*b+y);
              if(sq[i][j]=='*') trans[tnt++]=i*b+j;
          }
        for(int i=0;i<tnt;++i)
        {
            scanf("%d%d",&x,&y);
            if(check(x,y))
              AddEdge(trans[i],x*b+y);
        }
        int ans=solve();
        printf("%d\n",ans);
    }
    return 0;
}
