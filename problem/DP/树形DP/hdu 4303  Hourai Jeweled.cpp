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
const int maxn=300000+10;
const int maxv=100000+10;
struct Edge
{
    int v,w,next;
};
Edge edges[maxn<<1];
int head[maxn],nEdge,n;
int val[maxn],pa[maxn],cntp[maxn],S[maxn],c;
ll dp[maxn],cw[maxv],cv[maxv],ans;
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void dfs(int u,int fa)
{
    dp[u]=val[u];cntp[u]=1;
    ll sum=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        pa[v]=edges[k].w;
        dfs(v,u);
    }
    c=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        if(!cv[edges[k].w]) S[c++]=edges[k].w;
        cntp[u]+=cntp[v];
        cv[edges[k].w]+=cntp[v];
        cw[edges[k].w]+=dp[v];
        if(edges[k].w!=pa[u])
           dp[u]+=dp[v]+(ll)val[u]*cntp[v];
        ans+=dp[v]+(ll)val[u]*cntp[v];
        sum+=dp[v];
        ans+=(sum-cw[edges[k].w])*cntp[v]+dp[v]*(cntp[u]-1-cv[edges[k].w])+(ll)val[u]*cntp[v]*(cntp[u]-1-cv[edges[k].w]);
    }
    cntp[u]-=cv[pa[u]];
    while(c>0)
    {
        cv[S[--c]]=0;
        cw[S[c]]=0;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d",&n))
    {
        memset(head,0xff,sizeof(head));
        memset(cw,0,sizeof(cw));
        memset(cv,0,sizeof(cv));
        nEdge=-1;
        for(int i=1;i<=n;++i)
          scanf("%d",&val[i]);
        int u,v,w;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
        }
        ans=0;pa[1]=0;
        dfs(1,-1);
        printf("%I64d\n",ans);
    }
    return 0;
}
