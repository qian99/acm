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
const int maxm=maxn*maxn;
int level[maxn],val[maxn];
int d[maxn],m,n;
bool inq[maxn];
struct Edge
{
    int v,w,next;
};
Edge edges[maxm];
int head[maxn],nEdge,ans;
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void spfa(int limit)
{
    val[0]=limit;d[0]=0;
    memset(inq,0,sizeof(inq));
    for(int i=1;i<=n;++i) d[i]=val[i];
    queue<int>q;
    q.push(0);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(level[v]<limit||level[v]-limit>m) continue;
            if(d[v]>d[u]+edges[k].w||u==0)
            {
                d[v]=d[u]+edges[k].w;
                if(!inq[v]) {inq[v]=true;q.push(v);}
            }
        }
    }
    ans=min(ans,d[1]);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&m,&n))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int k,v,w;
        for(int i=1;i<=n;++i)
        {
            scanf("%d%d%d",&val[i],&level[i],&k);
            AddEdge(0,i,val[i]);
            for(int j=0;j<k;++j)
            {
                scanf("%d%d",&v,&w);
                AddEdge(v,i,w);
            }
        }
        ans=val[1];
        for(int i=1;i<=n;++i)
         spfa(level[i]);
        printf("%d\n",ans);
    }
    return 0;
}
