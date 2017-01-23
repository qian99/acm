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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 500000 + 10;
vector<int>G[maxn];
vector<pair<int,int> >querys[maxn];
int pa[maxn],d[maxn],anc[maxn],w[maxn],tot;
pair<int,int>op[maxn],np[maxn];
int vis[maxn],flag[maxn],cnt;
int Find(int x)
{
    return x == pa[x] ? x : pa[x] = Find(pa[x]);
}
void tarjan(int u)
{
    pa[u] = u;
    vis[u] = cnt;
    for(int i = 0;i < (int)querys[u].size();++i)
    {
        int v = querys[u][i].first;
        int x = querys[u][i].second;
        if(vis[v] == cnt)
        {
            np[tot++] = make_pair(d[Find(v)],x);
        }
    }
    for(int i = 0;i < (int)G[u].size();++i)
    {
        int v = G[u][i];
        d[v] = d[u] - 1;
        tarjan(v);
        pa[v] = u;
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    memset(anc,0xff,sizeof(anc));
    for(int i = 1; i <= n;++i)
        scanf("%d",&w[i]);
    for(int i = 1;i <= n + m;++i)
        pa[i] = i;
    int u,v;
    int N = n;
    for(int i = 1;i <= m;++i)
    {
        scanf("%d%d",&u,&v);
        u = Find(u);
        v = Find(v);
        N++;
        pa[u] = pa[v] = N;
        G[N].push_back(v);
        G[N].push_back(u);
        flag[u] = flag[v] = true;
    }
    for(int i = 1;i <= k;++i)
    {
        scanf("%d%d",&u,&v);
        op[i] = make_pair(u,v);
        querys[u].push_back(make_pair(v,i));
        querys[v].push_back(make_pair(u,i));
    }
    tot = cnt = 0;
    for(int i = 1; i <= N;++i)
        if(!flag[i])
        {
            cnt++;
            tarjan(i);
        }
    sort(np,np + tot);
    ll ans = 0;
    for(int i = 0;i < tot;++i)
    {
        int x = np[i].second;
        u = op[x].first;
        v = op[x].second;
        if(w[u] && w[v])
        {
            int y = min(w[u],w[v]);
            ans += y*2LL;
            w[u] -= y;
            w[v] -= y;
        }
    }
    cout<<ans<<endl;
    return 0;
}
