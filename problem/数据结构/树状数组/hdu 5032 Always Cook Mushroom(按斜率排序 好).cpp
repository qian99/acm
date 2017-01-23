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
const int maxn = 1000 + 10;
const int maxm = 100000 + 10;
struct BIT
{
    ll C[maxn];
    void add(int x,ll v)
    {
        for(;x < maxn; x += x&-x)
            C[x] += v;
    }
    ll sum(int x)
    {
        ll res = 0;
        for(;x > 0; x -= x&-x)
            res += C[x];
        return res;
    }
    void clear()
    {
        memset(C,0,sizeof(C));
    }
}tree;
struct Node
{
    int x,y,p,id;
    Node(int x = 0,int y = 0,int p = 0,int id = 0):x(x),y(y),p(p),id(id){}
    bool operator < (const Node & a) const
    {
        return (ll)y*a.x < (ll)a.y*x;
    }
}node[maxn*maxn],querys[maxm];
ll ans[maxm];
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int tot = 0;
    for(int i = 1;i <= 1000;++i)
        for(int j = 1;j <= 1000;++j)
            node[tot++] = Node(i,j,0,0);
    sort(node,node + tot);
    int A,B,t,m,tcase = 0;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&A,&B);
        scanf("%d",&m);
        int a,b,x;
        for(int i = 0;i < m;++i)
        {
            scanf("%d%d%d",&a,&b,&x);
            querys[i] = Node(a,b,x,i);
        }
        sort(querys,querys + m);
        tree.clear();
        int j = 0;
        for(int i = 0;i < m;++i)
        {
            while(j < tot && !(querys[i] < node[j]))
            {
                tree.add(node[j].x,(ll)(node[j].x + A)*(node[j].y + B));
                j++;
            }
            ans[querys[i].id] = tree.sum(querys[i].p);
        }
        printf("Case #%d:\n",++tcase);
        for(int i = 0;i < m;++i)
            printf("%I64d\n",ans[i]);
    }
    return 0;
}
