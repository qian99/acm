#pragma comment(linker, "/STACK:102400000,102400000")
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
const int size=255;
struct Edge
{
    int v,next;
    Edge(){}
    Edge(int v,int next):v(v),next(next){}
}edges[maxn];
struct Query
{
    int L,R,id;
    Query(){}
    Query(int L,int R,int id):L(L),R(R),id(id){}
    bool operator <(const Query & a) const
    {
        if(L/size!=a.L/size) return L<a.L;
        return R<a.R;
    }
}querys[maxn];
int val[maxn],num[maxn],cnt[maxn],Lv[maxn],Rv[maxn];
int head[maxn],ans[maxn],nEdge,dfs_clock,n,m,k,tot;
map<int,int>mp;
void Init()
{
    mp.clear();
    memset(head,0xff,sizeof(head));
    nEdge=-1;dfs_clock=0;
    memset(cnt,0,sizeof(cnt));
}
void AddEdges(int u,int v)
{
    edges[++nEdge]=Edge(v,head[u]);
    head[u]=nEdge;
    edges[++nEdge]=Edge(u,head[v]);
    head[v]=nEdge;
}
void dfs(int u,int fa)
{
    Lv[u]=++dfs_clock;
    val[dfs_clock]=num[u];
    for(int k=head[u];k!=-1;k=edges[k].next)
    {
        int v=edges[k].v;
        if(v==fa) continue;
        dfs(v,u);
    }
    Rv[u]=dfs_clock;
}
inline void Add(int x)
{
    if(cnt[val[x]]==k) tot--;
    if(cnt[val[x]]+1==k) tot++;
    cnt[val[x]]++;
}
inline void Dec(int x)
{
    if(cnt[val[x]]==k) tot--;
    if(cnt[val[x]]-1==k) tot++;
    cnt[val[x]]--;
}
void solve()
{
    tot=0;
    int l=1,r=0;
    for(int i=0;i<m;++i)
    {
        while(querys[i].L<l) Add(--l);
        while(querys[i].R<r) Dec(r--);
        while(querys[i].L>l) Dec(l++);
        while(querys[i].R>r) Add(++r);
        ans[querys[i].id]=tot;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        if(tcase) printf("\n");
        tcase++;
        Init();
        scanf("%d%d",&n,&k);
        int u=0,v;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&v);
            if(mp[v]) num[i]=mp[v];
            else num[i]=mp[v]=++u;
        }
        for(int i=1;i<n;++i)
        {
            scanf("%d%d",&u,&v);
            AddEdges(u,v);
        }
        dfs(1,-1);
        scanf("%d",&m);
        for(int i=0;i<m;++i)
        {
            scanf("%d",&u);
            querys[i]=Query(Lv[u],Rv[u],i);
        }
        sort(querys,querys+m);
        solve();
        printf("Case #%d:\n",tcase);
        for(int i=0;i<m;++i)
            printf("%d\n",ans[i]);
    }
    return 0;
}
