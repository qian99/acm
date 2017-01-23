#include <iostream>
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
const int maxn=100000+3000;
const int SIZE=300;
int bnt[maxn],block[maxn/SIZE+10],cnt[maxn];
int l[maxn],r[maxn],dfs_clock;
int c[maxn],cval[maxn],ans[maxn],n,m;
vector<int>g[maxn];
struct Query
{
    int l,r,k,id;
    Query(){}
    Query(int lx,int rx,int kk,int i){l=lx;r=rx;k=kk;id=i;}
    bool operator <(const Query &q) const
    {
        if(l/SIZE!=q.l/SIZE) return l<q.l;
        return r>q.r;
    }
}querys[maxn];
void dfs(int u,int fa)
{
    l[u]=++dfs_clock;
    cval[l[u]]=c[u];
    int sz=g[u].size();
    for(int i=0;i<sz;++i)
    {
        int v=g[u][i];
        if(v==fa) continue;
        dfs(v,u);
    }
    r[u]=dfs_clock;
}
void Insert(int k,int x)
{
    bnt[k]+=x;
    block[k/SIZE]+=x;
}
void Add(int v)
{
    int p=++cnt[cval[v]];
    Insert(p,1);
    Insert(p-1,-1);
}
void Dec(int v)
{
    int p=--cnt[cval[v]];
    Insert(p,1);
    Insert(p+1,-1);
}
int cal(int k)
{
    int sum=0,p=k/SIZE;
    for(int i=k;i<(p+1)*SIZE;++i)
        sum+=bnt[i];
    for(int i=p+1;i*SIZE<maxn;++i)
        sum+=block[i];
    return sum;
}
void solve()
{
    memset(cnt,0,sizeof(cnt));
    memset(bnt,0,sizeof(bnt));
    memset(block,0,sizeof(block));
    Insert(0,n);
    Add(1);
    int l=1,r=1;
    for(int i=0;i<m;++i)
    {
        while(querys[i].l<l) Add(--l);
        while(querys[i].r>r) Add(++r);
        while(querys[i].l>l) Dec(l++);
        while(querys[i].r<r) Dec(r--);
        ans[querys[i].id]=cal(querys[i].k);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n;++i) g[i].clear();
    dfs_clock=0;
    for(int i=1;i<=n;++i)
        scanf("%d",&c[i]);
    int u,v,k;
    for(int i=0;i<n-1;++i)
    {
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,-1);
    for(int i=0;i<m;++i)
    {
        scanf("%d%d",&v,&k);
        querys[i]=Query(l[v],r[v],k,i);
    }
    sort(querys,querys+m);
    solve();
    for(int i=0;i<m;++i)
        printf("%d\n",ans[i]);
    return 0;
}
