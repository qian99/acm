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
const int maxn=200000+10;
struct Node
{
    int L,x,R,type,id;
    Node(){}
    Node(int L,int x,int R,int type,int id=0):L(L),x(x),R(R),type(type),id(id){}
    bool operator <(const Node &a) const
    {
        return x==a.x?type<a.type:x<a.x;
    }
}node[maxn<<2];
struct SegTree
{
    int sum[maxn<<4];
    void PushUp(int rt)
    {
        sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    }
    void build(int l,int r,int rt)
    {
        sum[rt]=0;
        if(l==r) return ;
        int m=(l+r)>>1;
        build(l,m,rt<<1);
        build(m+1,r,rt<<1|1);
    }
    int Query(int L,int R,int l,int r,int rt)
    {
        if(l>=L&&r<=R) return sum[rt];
        int m=(l+r)>>1;
        int tot=0;
        if(m>=L) tot+=Query(L,R,l,m,rt<<1);
        if(m<R) tot+=Query(L,R,m+1,r,rt<<1|1);
        return tot;
    }
    void Update(int p,int l,int r,int rt)
    {
        if(l==r)
        {
            sum[rt]++;
            return ;
        }
        int m=(l+r)>>1;
        if(m>=p) Update(p,l,m,rt<<1);
        else Update(p,m+1,r,rt<<1|1);
        PushUp(rt);
    }
}tree;
vector<int>G[maxn<<2];
int Lx[maxn<<2],Rx[maxn<<2],ans[maxn<<2],dfs_clock;
int edge[maxn<<2][2],query[maxn<<2][3];
bool vis[maxn<<2];
void Init(int n)
{
    memset(vis,0,sizeof(vis));
    memset(ans,0,sizeof(ans));
    for(int i=0;i<=n;++i) G[i].clear();
    dfs_clock=0;
}
void dfs(int u)
{
    Lx[u]=++dfs_clock;
    vis[u]=true;
    for(int i=0;i<(int)G[u].size();++i)
        dfs(G[u][i]);
    Rx[u]=dfs_clock;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,q;
    while(~scanf("%d%d",&n,&m))
    {
        Init(n);
        for(int i=0;i<m;++i)
            scanf("%d%d",&edge[i][0],&edge[i][1]);
        scanf("%d",&q);
        int N=n;
        for(int i=0;i<q;++i)
        {
            scanf("%d%d%d",&query[i][0],&query[i][1],&query[i][2]);
            if(query[i][0]==2)
            {
                N++;
                G[N].clear();
                G[N].push_back(query[i][1]);
                G[N].push_back(query[i][2]);
                vis[query[i][1]]=vis[query[i][2]]=true;
            }
        }
        for(int i=1;i<=N;++i)
            if(!vis[i]) dfs(i);
        int tot=0;
        for(int i=0;i<m;++i)
            node[tot++]=Node(Lx[edge[i][0]],Lx[edge[i][1]],0,0);
        int x,y,idx=0;
        for(int i=0;i<q;++i)
        {
            if(query[i][0]==2) continue;
            x=query[i][1];
            y=query[i][2];
            node[tot++]=Node(Lx[x],Lx[y],Rx[x],-1,idx);
            node[tot++]=Node(Lx[x],Rx[y],Rx[x],1,idx++);
        }
        tree.build(1,N,1);
        sort(node,node+tot);
        for(int i=0;i<tot;++i)
        {
            if(node[i].type==0)
                tree.Update(node[i].L,1,N,1);
            else if(node[i].type==-1)
                ans[node[i].id]-=tree.Query(node[i].L,node[i].R,1,N,1);
            else ans[node[i].id]+=tree.Query(node[i].L,node[i].R,1,N,1);
        }
        for(int i=0;i<idx;++i)
            if(ans[i]>0) puts("YES");
            else puts("NO");
    }
    return 0;
}
