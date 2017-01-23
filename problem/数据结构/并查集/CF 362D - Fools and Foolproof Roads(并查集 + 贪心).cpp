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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 100000 + 10;
struct Node
{
    int u;
    ll val;
    Node(int u = 0,ll val = 0):u(u),val(val){}
    bool operator < (const Node & a) const
    {
        return val > a.val;
    }
};
int pa[maxn],ans[maxn][2];
ll cost[maxn];
int Find(int x)
{
    return x == pa[x]?x:pa[x] = Find(pa[x]);
}
priority_queue<Node>que;
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m,p,q;
    scanf("%d%d%d%d",&n,&m,&p,&q);
    for(int i = 1;i <= n;++i)
    {
        pa[i] = i;
        cost[i] = 0;
    }
    int ux = -1,uy = -1,u,v,w,x,y;
    int tot = n;
    for(int i = 0;i < m;++i)
    {
        scanf("%d%d%d",&u,&v,&w);
        x = Find(u);
        y = Find(v);
        if(x != y)
        {
            pa[y] = x;
            cost[x] += cost[y];
            tot--;
        }
        cost[x] += w;
        ux = u;
        uy = v;
    }
    if(tot < q)
    {
        puts("NO");
        return 0;
    }
    for(int i = 1;i <= n;++i)
        if(pa[i] == i) que.push(Node(i,cost[i]));
    Node na,nb;
    int cnt = 0;
    while(tot > q && p > 0)
    {
        if(que.empty()) break;
        na = que.top();que.pop();
        if(que.empty()) break;
        nb = que.top();que.pop();
        pa[nb.u] = pa[na.u];
        cost[na.u] += cost[nb.u];
        cost[na.u] = cost[na.u] + min(cost[na.u]+1,(ll)1e9);
        ans[cnt][0] = na.u;
        ans[cnt++][1] = nb.u;
        ux = na.u; uy = nb.u;
        que.push(Node(na.u,cost[na.u]));
        p--;tot--;
    }
    if(tot > q)
    {
        puts("NO");
        return 0;
    }
    if(p)
    {
        if(ux == - 1)
        {
            puts("NO");
            return 0;
        }
        while(p--)
        {
            ans[cnt][0] = ux;
            ans[cnt++][1] = uy;
        }
    }
    puts("YES");
    for(int i = 0;i < cnt;++i)
        printf("%d %d\n",ans[i][0],ans[i][1]);
    return 0;
}