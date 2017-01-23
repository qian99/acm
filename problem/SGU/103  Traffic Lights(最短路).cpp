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
const int maxn=300+10;
const int maxm=14000+10;
struct Node
{
    int c,r;
    int t[2];
};
Node node[maxn];
struct Edge
{
    int v,next;
    int w;
};
Edge edges[maxm<<1];
int head[maxn],nEdge,n,m,s,t;
int d[maxn],pa[maxn],res[maxn];
bool inq[maxn];
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
int gettime(int st,int u,int v)
{
    int cu,cv,c,tmp,ut,vt;
    if(st<node[u].r) cu=node[u].c,ut=node[u].r-st;
    else
    {
        c=node[u].c;
        tmp=(st-node[u].r);
        tmp=tmp%(node[u].t[0]+node[u].t[1]);
        if(tmp<node[u].t[c^1]) cu=c^1,ut=node[u].t[c^1]-tmp;
        else cu=c,ut=node[u].t[0]+node[u].t[1]-tmp;
    }
    if(st<node[v].r) cv=node[v].c,vt=node[v].r-st;
    else
    {
        c=node[v].c;
        tmp=(st-node[v].r);
        tmp=tmp%(node[v].t[0]+node[v].t[1]);
        if(tmp<node[v].t[c^1]) cv=c^1,vt=node[v].t[c^1]-tmp;
        else cv=c,vt=node[v].t[0]+node[v].t[1]-tmp;
    }
    if(cu==cv) return 0;
    if(ut==vt)
    {
        if(node[u].t[cu^1]==node[v].t[cv^1])
        {
            if(node[u].t[cu]==node[v].t[cv]) return inf;
            return ut+node[u].t[cu^1]+min(node[u].t[cu],node[v].t[cv]);
        }
        else
        return ut+min(node[u].t[cu^1],node[v].t[cv^1]);
    }
    return min(ut,vt);
}
int spfa()
{
    memset(inq,0,sizeof(inq));
    memset(pa,0,sizeof(pa));
    for(int i=1;i<=n;++i) d[i]=inf;
    d[s]=0;
    queue<int>q;
    q.push(s);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        inq[u]=false;
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            int tmp=gettime(d[u],u,v);
            if(d[v]>d[u]+tmp+edges[k].w)
            {
                d[v]=d[u]+tmp+edges[k].w;
                pa[v]=u;
                if(!inq[v]) {inq[v]=true;q.push(v);}
            }
        }
    }
    if(d[t]==inf) return 0;
    return d[t];
}
void printpath()
{
    int cnt=0;
    int u=t;
    while(u!=s&&u)
    {
        res[cnt++]=u;
        u=pa[u];
    }
    printf("%d",s);
    for(int i=cnt-1;i>=0;--i)
      printf(" %d",res[i]);
    printf("\n");
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&s,&t))
    {
        scanf("%d%d",&n,&m);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        char str[3];
        for(int i=1;i<=n;++i)
        {
            scanf("%s%d%d%d",str,&node[i].r,&node[i].t[0],&node[i].t[1]);
            if(str[0]=='B') node[i].c=0;
            else node[i].c=1;
        }
        int u,v,w;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            AddEdge(u,v,w);
            AddEdge(v,u,w);
        }
        int ans=spfa();
        printf("%d\n",ans);
        if(ans) printpath();
    }
    return 0;
}
