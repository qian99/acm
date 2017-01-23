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
const int maxn = 200000+10;
struct Node
{
    int l,r;
    Node(int l = 0,int r = 0):l(l),r(r){}
    bool operator < (const Node & a) const
    {
        return (l==a.l && r < a.r) || (l < a.l);
    }
}tree[2][maxn];
int hashval[2][maxn],num[2][maxn],cnt;
int q[maxn],tail;
map<Node, int>tval;
inline int getv(Node x)
{
    if(tval.find(x) == tval.end())
        return tval[x] = ++cnt;
    return tval[x];
}
void dfs(int u,int kind)
{
    tail = 0;
    q[tail++] = u;
    for(int head = 0; head < tail;++head)
    {
        u = q[head];
        if(tree[kind][u].l != -1)
            q[tail++] = tree[kind][u].l;
        if(tree[kind][u].r != -1)
            q[tail++] = tree[kind][u].r;
    }
    Node ntmp;
    int id;
    for(int i = tail - 1 ;i >= 0;--i)
    {
        u = q[i];
        if(tree[kind][u].l == -1) ntmp.l = 0;
        else ntmp.l = hashval[kind][tree[kind][u].l];
        if(tree[kind][u].r == -1) ntmp.r = 0;
        else ntmp.r = hashval[kind][tree[kind][u].r];
        id = getv(ntmp);
        num[kind][id]++;
        hashval[kind][u] = id;
    }
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t,n,m;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        int a,b;
        for(int i = 1;i <= n;++i)
        {
            scanf("%d%d",&a,&b);
            tree[0][i].l = a;
            tree[0][i].r = b;
        }
        for(int i = 1;i <= m;++i)
        {
            scanf("%d%d",&a,&b);
            tree[1][i].l = a;
            tree[1][i].r = b;
        }
        cnt = 0;
        tval.clear();
        memset(num,0,sizeof(num));
        dfs(1,0);
        dfs(1,1);
        ll ans = 0;
        for(int i = 1;i <= cnt;++i)
            ans += (ll)num[0][i]*num[1][i];
        printf("%lld\n",ans);
    }
    return 0;
}
