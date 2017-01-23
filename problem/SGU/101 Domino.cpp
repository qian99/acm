//把每个Domino看成一条边，求欧拉通路
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
const int maxn=10;
const int maxm=100+10;
struct Edge
{
    int v,next;
};
Edge edges[maxm<<1];
int head[maxn],nEdge,cntb;
int degree[maxn];
bool vis[maxm<<1],flag1[maxn],flag2[maxn];
int ans[maxm];
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void clearAll()
{
    memset(head,0xff,sizeof(head));
    memset(vis,0,sizeof(vis));
    memset(flag1,0,sizeof(flag1));
    memset(flag2,0,sizeof(flag2));
    memset(degree,0,sizeof(degree));
    nEdge=-1;
}
void dfs(int u)
{
    flag2[u]=true;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        if(!vis[k])
        {
            vis[k]=vis[k^1]=true;
            dfs(edges[k].v);
            ans[cntb++]=k;
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int m;
    while(~scanf("%d",&m))
    {
        int u,v;
        clearAll();
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
            AddEdge(v,u);
            degree[u]++;degree[v]++;
            flag1[u]=flag1[v]=true;
        }
        bool canfind=true;
        int cnt=0,s=-1,st;
        for(int i=0;i<=6;++i)
          if(flag1[i])
          {
              if(degree[i]&1) cnt++,s=i;
              st=i;
          }
        if(cnt!=0&&cnt!=2) canfind=false;
        if(s==-1) s=st;
        cntb=0;
        dfs(s);
        for(int i=0;i<=6;++i)
          if(flag1[i]&&!flag2[i]) canfind=false;
        if(!canfind)
          printf("No solution\n");
        else
        {
            for(int i=0;i<m;++i)
            {
                printf("%d ",ans[i]/2+1);
                if((ans[i]^1)&1) printf("-\n");
                else printf("+\n");
            }
        }
    }
    return 0;
}
