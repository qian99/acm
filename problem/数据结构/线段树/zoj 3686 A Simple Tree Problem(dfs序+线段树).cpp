#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<stack>
#include<set>
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
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxn<<1];
int head[maxn],lx[maxn],rx[maxn],nEdge,dfs_clock;
void AddEdge(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
void dfs(int u,int fa)
{
    lx[u]=++dfs_clock;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        if(edges[k].v==fa) continue;
        dfs(edges[k].v,u);
    }
    rx[u]=dfs_clock;
}
int sum[maxn<<2][2],flip[maxn<<2];
void PushUp(int rt)
{
    sum[rt][0]=sum[rt<<1][0]+sum[rt<<1|1][0];
    sum[rt][1]=sum[rt<<1][1]+sum[rt<<1|1][1];
}
void PushDown(int rt)
{
    if(flip[rt])
    {
        flip[rt<<1]^=1;
        flip[rt<<1|1]^=1;
        swap(sum[rt<<1][0],sum[rt<<1][1]);
        swap(sum[rt<<1|1][0],sum[rt<<1|1][1]);
        flip[rt]=0;
    }
}
int Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        return sum[rt][1];
    }
    int m=(l+r)>>1;
    PushDown(rt);
    int tot=0;
    if(m>=L) tot+=Query(L,R,l,m,rt<<1);
    if(m<R) tot+=Query(L,R,m+1,r,rt<<1|1);
    return tot;
}
void Update(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        flip[rt]^=1;
        swap(sum[rt][0],sum[rt][1]);
        return ;
    }
    int m=(l+r)>>1;
    PushDown(rt);
    if(m>=L) Update(L,R,l,m,rt<<1);
    if(m<R) Update(L,R,m+1,r,rt<<1|1);
    PushUp(rt);
}
void build(int l,int r,int rt)
{
    flip[rt]=0;
    if(l==r)
    {
        sum[rt][0]=1;
        sum[rt][1]=0;
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    char str[10];
    while(~scanf("%d%d",&n,&m))
    {
        memset(head,0xff,sizeof(head));
        nEdge=-1;dfs_clock=0;
        int u;
        for(int i=2;i<=n;++i)
        {
            scanf("%d",&u);
            AddEdge(i,u);
        }
        dfs(1,-1);
        build(1,n,1);
        while(m--)
        {
            scanf("%s%d",str,&u);
            if(str[0]=='o')
                Update(lx[u],rx[u],1,n,1);
            else
            {
                int ans=Query(lx[u],rx[u],1,n,1);
                printf("%d\n",ans);
            }
        }
        printf("\n");
    }
    return 0;
}
