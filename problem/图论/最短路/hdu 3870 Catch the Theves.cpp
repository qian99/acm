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
const int maxn=500000+10;
const int maxm=700000+10;
struct Edge
{
    int v,w,next;
};
Edge edges[maxm<<1];
int head[maxn],nEdge,n,N;
int d[maxn],a[410][410];
bool inq[maxn];
void AddEdge(int u,int v,int w)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].w=w;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
void spfa()
{
    memset(inq,0,sizeof(inq));
    for(int i=0;i<=N;++i) d[i]=inf;
    d[0]=0;
    queue<int>q;
    q.push(0);
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
                if(!inq[v]){inq[v]=true;q.push(v);}
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
        scanf("%d",&n);
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        for(int i=0;i<n;++i)
         for(int j=0;j<n;++j)
           scanf("%d",&a[i][j]);
        N=(n-1)*(n-1)+1;
        int u,v;
        for(int i=0;i<n-1;++i)
         for(int j=0;j<n-1;++j)
         {
             u=i*(n-1)+j+1;
             v=u-n+1;
             if(v<=0) v=N;
             AddEdge(u,v,a[i][j]);
             AddEdge(v,u,a[i][j]);
             v=u-1;
             if(v%(n-1)==0) v=0;
             AddEdge(u,v,a[i][j]);
             AddEdge(v,u,a[i][j]);
         }
        for(int i=0;i<n-1;++i)
        {
            u=(n-2)*(n-1)+i+1;
            AddEdge(u,0,a[n-1][i]);
            AddEdge(0,u,a[n-1][i]);
            u=(i+1)*(n-1);
            AddEdge(u,N,a[i][n-1]);
            AddEdge(N,u,a[i][n-1]);
        }
        spfa();
        printf("%d\n",d[N]);
    }
    return 0;
}
