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
const int maxn=50000+10;
struct Edge
{
    int v,next;
    Edge(int v=0,int next=0):v(v),next(next){}
}edges[maxn<<1];
struct Node
{
    int u,loy,abt;
    Node(int u=0,int loy=0,int abt=0):u(u),loy(loy),abt(abt) {}
    bool operator <(const Node &a) const
    {
        return abt>a.abt;
    }
}node[maxn];
int head[maxn],Lx[maxn],Rx[maxn],nEdge,dfs_clock,n;
int maxv[maxn<<2],ans[maxn];
map<int,int>mp;
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    nEdge=-1;dfs_clock=0;
    mp.clear();
}
void dfs(int u)
{
    Lx[u]=++dfs_clock;
    for(int k=head[u];k!=-1;k=edges[k].next)
        dfs(edges[k].v);
    Rx[u]=dfs_clock;
}
void PushUp(int rt)
{
    maxv[rt]=max(maxv[rt<<1],maxv[rt<<1|1]);
}
void build(int l,int r,int rt)
{
    maxv[rt]=-1;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
int Query(int L,int R,int l,int r,int rt)
{
    if(L>R) return -1;
    if(l>=L&&r<=R) return maxv[rt];
    int m=(l+r)>>1;
    if(m>=R) return Query(L,R,l,m,rt<<1);
    else if(m<L) return Query(L,R,m+1,r,rt<<1|1);
    return max(Query(L,R,l,m,rt<<1),Query(L,R,m+1,r,rt<<1|1));
}
void Update(int p,int l,int r,int rt,int val)
{
    if(l==r)
    {
        maxv[rt]=val;
        return ;
    }
    int m=(l+r)>>1;
    if(m>=p) Update(p,l,m,rt<<1,val);
    else Update(p,m+1,r,rt<<1|1,val);
    PushUp(rt);
}
void solve()
{
    dfs(0);
    build(1,n,1);
    for(int i=1;i<n;++i)
    {
        int lim=i;
        while(lim<n&&node[i].abt==node[lim].abt) lim++;
        for(int j=i;j<lim;++j)
        {
            int tmp=Query(Lx[node[j].u]+1,Rx[node[j].u],1,n,1);
            if(tmp==-1) ans[node[j].u]=-1;
            else ans[node[j].u]=mp[tmp];
        }
        for(int j=i;j<lim;++j)
            Update(Lx[node[j].u],1,n,1,node[j].loy);
        i=lim-1;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        Init();
        int fa;
        for(int i=1;i<n;++i)
        {
            scanf("%d",&fa);
            AddEdges(fa,i);
            scanf("%d%d",&node[i].loy,&node[i].abt);
            mp[node[i].loy]=i;
            node[i].u=i ;
        }
        sort(node+1,node+n);
        solve();
        int u;
        while(m--)
        {
            scanf("%d",&u);
            printf("%d\n",ans[u]);
        }
    }
    return 0;
}
