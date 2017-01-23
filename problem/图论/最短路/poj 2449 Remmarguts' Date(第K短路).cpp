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
const int maxn=1000+10;
const int maxm=100000+10;
struct Edge
{
    int v,w,next;
    Edge () {};
    Edge (int vv,int ww,int nn) {v=vv;w=ww;next=nn;}
}edges[maxm<<1];
int head[maxn<<1],nEdge;
int n,m,S,T,K;
int d[maxn],cnt[maxn];
bool inq[maxn];
struct Node
{
    int u,len;
    Node () {};
    Node (int uu,int l) {u=uu;len=l;}
    bool operator <(const Node & a ) const
    {
        return d[u]+len>d[a.u]+a.len;
    }
};
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge]=Edge(v,w,head[u]);
    head[u]=nEdge;
}
void spfa()
{
    memset(d,0x3f,sizeof(d));
    memset(inq,0,sizeof(inq));
    d[T]=0;
    queue<int>q;
    q.push(T);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u+n];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v-n;
            if(d[v]>d[u]+edges[k].w)
            {
                d[v]=d[u]+edges[k].w;
                if(!inq[v]) {inq[v]=true;q.push(v);}
            }
        }
    }
}
int astar()
{
    if(d[S]==inf) return -1;
    memset(cnt,0,sizeof(cnt));
    priority_queue<Node>q;
    q.push(Node(S,0));
    while(!q.empty())
    {
        Node node=q.top();q.pop();
        int u=node.u;
        cnt[u]++;
        if(cnt[T]==K) return node.len;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            q.push(Node(v,edges[k].w+node.len));
        }
    }
    return -1;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    memset(head,0xff,sizeof(head));
    nEdge=-1;
    int u,v,w;
    for(int i=0;i<m;++i)
    {
        scanf("%d%d%d",&u,&v,&w);
        AddEdge(u,v,w);
        AddEdge(v+n,u+n,w);
    }
    scanf("%d%d%d",&S,&T,&K);
    if(S==T) K++;
    spfa();
    int ans=astar();
    printf("%d\n",ans);
    return 0;
}

