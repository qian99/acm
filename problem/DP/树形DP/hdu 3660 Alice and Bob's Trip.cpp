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
const int maxn=500000+10;
struct Edge
{
    int v,w;
    int next;
};
Edge edges[maxn];
int head[maxn],nEdge,L,R;
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
int dpmax[maxn],dpmin[maxn],len[maxn];
int dfs(int u,int turns)
{
    if(len[u]>R) return 0;
    dpmax[u]=len[u];dpmin[u]=len[u];
    bool flag=false;
    int maxt=-1,mint=inf;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        len[v]=len[u]+edges[k].w;
        if(dfs(v,turns^1))
        {
            flag=true;
            if(turns==0)
              maxt=max(maxt,dpmin[v]);
            else mint=min(mint,dpmax[v]);
        }
    }
    if(flag)
    {
        if(turns==0) dpmax[u]=maxt;
        else dpmin[u]=mint;
    }
    if(!flag&&(len[u]<L||len[u]>R)) return 0;
    return 1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d%d%d",&n,&L,&R))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,w;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
        }
        len[0]=0;
        if(!dfs(0,0))
          printf("Oh, my god!\n");
        else printf("%d\n",dpmax[0]);
    }
    return 0;
}
