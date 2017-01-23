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
const int maxn = 2500 + 10;
const int maxm = 25000 + 10;
struct Edge
{
    int u,v,w,id;
    Edge(int u = 0,int v = 0,int w = 0,int id = 0):u(u),v(v),w(w),id(id){}
    bool operator < (const Edge & a) const
    {
        return w < a.w;
    }
}edges[maxm];
vector<pair<int,int> >G[maxn];
bool vis[maxn],flag[maxm];
int ans[maxm];
bool cmp(Edge a,Edge b)
{
    return a.id < b.id;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        int n,m,S;
        scanf("%d%d%d",&n,&m,&S);
        for(int i = 0;i <= n;++i) G[i].clear();
        int u,v,w;
        for(int i = 0;i < m;++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            edges[i] = Edge(u,v,w,i);
            G[u].push_back(make_pair(v,i));
            G[v].push_back(make_pair(u,i));
        }
//        sort(edges,edges + m);
        queue<int>q;
        q.push(S);
        memset(vis,0,sizeof(vis));
        memset(flag,0,sizeof(flag));
        vis[S] = true;
        int id,cnt = 0;
        while(!q.empty())
        {
            u = q.front();q.pop();
            for(int i = 0;i < (int)G[u].size();++i)
            {
                v = G[u][i].first;
                id = G[u][i].second;
                if(vis[v]) continue;
                vis[v] = true;
                q.push(v);
                flag[id] = true;
                ans[id] = ++cnt;
            }
        }
        for(int i = 0;i < m;++i)
            if(!flag[i]) ans[i] = ++cnt;
        sort(edges,edges + m,cmp);
        printf("Case %d:\n",++tcase);
        for(int i = 0;i < m;++i)
            printf("%d %d %d\n",edges[i].u,edges[i].v,ans[i]);
    }
    return 0;
}

