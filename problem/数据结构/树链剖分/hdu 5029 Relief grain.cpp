#pragma comment(linker,"/STACK:100000000,100000000")
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
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
struct Edge
{
    int u,v,next;
    Edge(){};
    Edge(int uu,int vv,int nx) {u=uu;v=vv;next=nx;}
}edges[maxn<<1];
int d[maxn],pa[maxn],fp[maxn],vson[maxn],num[maxn],xx[maxn];
int head[maxn],id[maxn],val[maxn],nEdge,N,n;
vector<pair<int,int> >Querys[maxn];
int ans[maxn];
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(u,v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(v,u,head[v]);
    head[v]=nEdge;
}
void Init()
{
    memset(head,0xff,sizeof(head));
    memset(d,0,sizeof(d));
    memset(vson,0xff,sizeof(vson));
    memset(id,0xff,sizeof(id));
    nEdge=-1;N=0;
    for(int i = 0; i < maxn;++i)
        Querys[i].clear();
}
int dfs(int u,int fa)
{
    int csum=1,cmax=0,me=-1;
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        d[v]=d[u]+1;pa[v]=u;
        int cc=dfs(v,u);
        csum+=cc;
        if(cc>cmax) {cmax=cc;me=v;}
    }
    vson[u]=me;
    return csum;
}
void dfs2(int u,int fa)
{
    if(vson[u]!=-1)
    {
        id[u]=++N;
        xx[N] = u;
        if(fa==-1||vson[fa]!=u) fp[u]=u;
        else fp[u]=fp[fa];
        dfs2(vson[u],u);
    }
    else if(fa==-1||vson[fa]==u)
        id[u]=++N,xx[N] = u,fp[u]=(fa==-1)?u:fp[fa];
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa||v==vson[u]) continue;
        fp[v]=v;
        if(vson[v] == -1)
        {
            id[v] = ++N;
            xx[N] = v;
        }
        dfs2(v,u);
    }
}
void add(int x,int y,int c)
{
    while(fp[x]!=fp[y])
    {
        if(d[fp[x]]<d[fp[y]])
            swap(x,y);
        int L = id[fp[x]];
        int R = id[x];
        if(L > R) swap(L,R);
        R++;
        Querys[L].push_back(make_pair(c,1));
        Querys[R].push_back(make_pair(c,-1));
        x=pa[fp[x]];
    }
    if(d[x]<d[y])
    {
        swap(x,y);
    }
    int L = id[y];
    int R = id[x];
    if(L > R) swap(L,R);
    R++;
    Querys[L].push_back(make_pair(c,1));
    Querys[R].push_back(make_pair(c,-1));
}
struct SegTree
{
    int maxv[maxn<<2],maxpos[maxn<<2];
    void PushUp(int rt)
    {
        if(maxv[rt<<1] >= maxv[rt<<1|1])
        {
            maxv[rt] = maxv[rt<<1];
            maxpos[rt] = maxpos[rt<<1];
        }
        else
        {
            maxv[rt] = maxv[rt<<1|1];
            maxpos[rt] = maxpos[rt<<1|1];
        }
    }
    void build(int l,int r,int rt)
    {
        maxv[rt] = 0;
        maxpos[rt] = l;
        if(l == r) return ;
        int m = (l + r)>>1;
        build(l,m,rt<<1);
        build(m+1,r,rt<<1|1);
    }
    void Update(int p,int l,int r,int rt,int v)
    {
        if(l == r)
        {
            maxv[rt] += v;
            return ;
        }
        int m = (l + r)>>1;
        if(m >= p) Update(p,l,m,rt<<1,v);
        else Update(p,m+1,r,rt<<1|1,v);
        PushUp(rt);
    }
    int Query(int L,int R,int l,int r,int rt,int & p)
    {
        if(l >= L && r <= R)
        {
            p = maxpos[rt];
            return maxv[rt];
        }
        int m = (l + r)>>1;
        if(m >= R) return Query(L,R,l,m,rt<<1,p);
        else if(m < L) return Query(L,R,m+1,r,rt<<1|1,p);
        else
        {
            int r1,r2,p1,p2;
            r1 = Query(L,R,l,m,rt<<1,p1);
            r2 = Query(L,R,m+1,r,rt<<1|1,p2);
            if(r2 > r1)
                r1 = r2,p1 = p2;
            p = p1;
            return r1;
        }
    }
}tree;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        if(n == 0 && m == 0) break;
        Init();
        int u,v;
        for(int i = 1;i < n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        dfs(1,-1);
        dfs2(1,-1);
        int c;
        int M = 0;
        for(int i = 0;i < m;++i)
        {
            scanf("%d%d%d",&u,&v,&c);
            add(u,v,c);
            M = max(M,c);
        }
        M++;
        tree.build(1,M,1);
        for(int i = 1;i <= N;++i)
        {
            u = xx[i];
            for(int j = 0;j < (int)Querys[i].size();++j)
            {
                int p =Querys[i][j].first;
                int cc = Querys[i][j].second;
                tree.Update(p,1,M,1,cc);
            }
            if(tree.maxv[1])
            {
                ans[u] = tree.maxpos[1];
            }
            else
                ans[u] = 0;
        }
        for(int i = 1;i <= n;++i)
            printf("%d\n",ans[i]);
    }
    return 0;
}
