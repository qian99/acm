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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000+10;
const int maxm=100000+10;
struct Edge
{
    int v,w,next;
    Edge(){}
    Edge(int v,int w,int next):v(v),w(w),next(next){}
}edges[maxm<<1];
int head[maxn],dmax[maxn],dmin[maxn],nEdge;
int fuel[maxn],sell[maxn],n,m,C;
bool inq[maxn];
void AddEdges(int u,int v,int w)
{
    edges[++nEdge]=Edge(v,w,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,w,head[v]);
    head[v]=nEdge;
}
void fmax(int s)
{
    memset(dmax,0xff,sizeof(dmax));
    memset(inq,0,sizeof(inq));
    queue<int>q;
    q.push(s);
    dmax[s]=C;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            if(dmax[u]<edges[k].w||(k&1)) continue;
            int v=edges[k].v;
            if(dmax[v]<dmax[u]-edges[k].w)
            {
                if(fuel[v]) dmax[v]=C;
                else dmax[v]=dmax[u]-edges[k].w;
                if(!inq[v]) {inq[v]=true;q.push(v);}
            }
        }
    }
}
void fmin(int s)
{
    memset(dmin,0x3f,sizeof(dmin));
    memset(inq,0,sizeof(inq));
    queue<int>q;
    q.push(s);
    dmin[s]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            if(dmin[u]+edges[k].w>C||(k%2==0)) continue;
            int v=edges[k].v;
            if(dmin[v]>dmin[u]+edges[k].w)
            {
                if(fuel[v]) dmin[v]=0;
                else dmin[v]=dmin[u]+edges[k].w;
                if(!inq[v]) {inq[v]=true;q.push(v);}
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d%d",&n,&m,&C))
    {
        memset(head,0xff,sizeof(head));
        memset(fuel,0,sizeof(fuel));
        memset(sell,0,sizeof(sell));
        nEdge=-1;
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdges(u,v,w);
        }
        int P,Q;
        scanf("%d",&P);
        while(P--)
        {
            scanf("%d",&u);
            fuel[u]=1;
        }
        scanf("%d",&Q);
        while(Q--)
        {
            scanf("%d%d",&u,&w);
            sell[u]=w;
        }
        fmax(1);
        fmin(n);
        int ans=0,tmp;
        for(int i=1;i<=n;++i)
            if(sell[i]&&dmax[i]!=-1&&dmin[i]!=inf)
            {
                tmp=(dmax[i]-dmin[i])*sell[i];
                ans=max(ans,tmp);
            }
        if(dmax[n]==-1) ans=-1;
        printf("%d\n",ans);
    }
    return 0;
}