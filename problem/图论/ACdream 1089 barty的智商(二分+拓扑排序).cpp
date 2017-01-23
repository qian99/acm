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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=10000+10;
struct Edge
{
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxn<<1];
struct Node
{
    int u,v,w;
    Node(){}
    Node(int u,int v,int w):u(u),v(v),w(w){}
}node[maxn<<1];
int head[maxn],degree[maxn],nEdge,n,m;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
}
bool check(int mid)
{
    memset(head,0xff,sizeof(head));
    memset(degree,0,sizeof(degree));
    nEdge=-1;
    for(int i=0;i<m;++i)
        if(node[i].w>mid)
        {
            AddEdges(node[i].u,node[i].v);
            degree[node[i].v]++;
        }
    queue<int>q;
    for(int i=1;i<=n;++i)
        if(degree[i]==0) q.push(i);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int k=head[u];k!=-1;k=edges[k].next)
        {
            int v=edges[k].v;
            degree[v]--;
            if(degree[v]==0)
            {
                q.push(v);
            }
        }
    }
    for(int i=1;i<=n;++i)
        if(degree[i]) return false;
    return true;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int u,v,w;
        scanf("%d%d",&n,&m);
        int L=0,R=0;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d%d",&v,&u,&w);
            node[i]=Node(u,v,w);
            R=max(R,w);
        }
        while(L<R)
        {
            int m=(L+R)>>1;
            if(check(m)) R=m;
            else L=m+1;
        }
        printf("%d\n",L);
    }
    return 0;
}