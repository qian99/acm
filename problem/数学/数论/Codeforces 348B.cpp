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
const int maxn=100000+10;
struct Edge
{
    int v,next;
};
Edge edges[maxn<<1];
int head[maxn],nEdge;
int w[maxn];
void AddEdge(int u,int v)
{
    nEdge++;
    edges[nEdge].v=v;
    edges[nEdge].next=head[u];
    head[u]=nEdge;
}
ll val[maxn],fz[maxn];
ll gcd(ll a,ll b)
{
    ll c;
    while(b!=0)
    {
        c=b;
        b=a%b;
        a=c;
    }
    return a;
}
ll lcm(ll a,ll b)
{
    return a*b/gcd(a,b);
}
void dfs(int u,int fa)
{
    ll a=-1,x=-1,b,y;
    int child=0;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        child++;
        dfs(v,u);
        if(a==-1)
          a=val[v],x=fz[v];
        else
        {
            b=val[v];y=fz[v];
            if(a==0||b==0)
            {
                a=0;
                continue;
            }
            ll c=min(a,b)-min(a,b)%lcm(x,y);
            x=lcm(x,y);
            a=c;
        }
    }
    if(child==0)
    {
        val[u]=w[u];
        fz[u]=1;
    }
    else
    {
        val[u]=a*child;
        fz[u]=x*child;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;
        ll sum=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&w[i]);
            sum+=w[i];
        }
        int u,v;
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
            AddEdge(v,u);
        }
        dfs(1,-1);
        sum-=val[1];
        printf("%I64d\n",sum);
    }
    return 0;
}
