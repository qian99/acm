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
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=50000+10;
const int maxm=50000+10;
struct Edge
{
    int v,w,next;
    Edge (){};
    Edge (int vv,int ww,int nn) {v=vv;w=ww;next=nn;}
}edges[maxm<<1];
int head[maxn],nEdge;
int val[maxn],n,m;
ll d[maxn];
bool inq[maxn];
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge]=Edge(v,w,head[u]);
    head[u]=nEdge;
}
void spfa()
{
    for(int i=1;i<=n;++i) d[i]=Inf;
    memset(inq,0,sizeof(inq));
    d[1]=0;
    queue<int>q;
    q.push(1);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            if(d[v]>d[u]+edges[k].w)
            {
                d[v]=d[u]+edges[k].w;
                if(!inq[v]) {inq[v]=true;q.push(v);}
            }
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        int u,v,w;
        for(int i=1;i<=n;++i)
            scanf("%d",&val[i]);
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
        }
        spfa();
        ll ans=0;
        for(int i=1;i<=n;++i)
        {
            if(d[i]==Inf) {ans=-1;break;}
            ans+=d[i]*val[i];
        }
        if(ans==-1) printf("No Answer\n");
        else printf("%I64d\n",ans);
    }
    return 0;
}

