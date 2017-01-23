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
const int maxn = 1000000 + 10;
struct Node
{
    int l,r,id;
    bool operator < (const Node & a) const
    {
        if(l != a.l) return l > a.l;
        if(r != a.r) return r < a.r;
        return id < a.id;
    }
}node[maxn];
int C[maxn],ans[maxn];
void add(int x)
{
    for(;x < maxn;x += x&-x)
        C[x]++;
}
int sum(int x)
{
    int res = 0;
    for(; x > 0; x -= x&-x)
        res += C[x];
    return res;
}
int main()
{
//    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,tot = 0;
    scanf("%d%d",&n,&m);
    for(int i = 0;i < n;++i)
    {
        scanf("%d%d",&node[tot].l,&node[tot].r);
        node[tot++].id = 0;
    }
    int cnt,p,last = 0;
    for(int i = 1;i <= m;++i)
    {
        scanf("%d",&cnt);
        ans[i] = n;
        last = 0;
        for(int j = 0; j < cnt;++j)
        {
            scanf("%d",&p);
            node[tot].l = last+1;
            node[tot].r = p - 1;
            if(node[tot].l <= node[tot].r)
                node[tot++].id = i;
            last = p;
        }
        node[tot].l = last + 1;
        node[tot].r = 1e6 + 1;
        node[tot++].id = i;
    }
    sort(node,node + tot);
    for(int i = 0;i < tot;++i)
        if(node[i].id)
            ans[node[i].id] -= sum(node[i].r);
        else
            add(node[i].r);
    for(int i = 1;i <= m;++i)
        printf("%d\n",ans[i]);
    return 0;
}