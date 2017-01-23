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
ll maxv[maxn<<2],addv[maxn<<2];
int a[maxn];
inline void PushUp(int rt)
{
    maxv[rt] = max(maxv[rt<<1],maxv[rt<<1|1]);
}
inline void PushDown(int rt)
{
    if(addv[rt])
    {
        addv[rt<<1] += addv[rt];
        addv[rt<<1|1] += addv[rt];
        maxv[rt<<1] += addv[rt];
        maxv[rt<<1|1] += addv[rt];
        addv[rt] = 0;
    }
}
void build(int l,int r,int rt)
{
    addv[rt] = 0;
    maxv[rt] = -Inf;
    if(l == r) return ;
    int m = (l + r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
void Update(int L,int R,int l,int r,int rt,int v)
{
    if(l >= L && r <= R)
    {
        addv[rt] += v;
        maxv[rt] += v;
        return ;
    }
    PushDown(rt);
    int m = (l + r)>>1;
    if(m >= L) Update(L,R,l,m,rt<<1,v);
    if(m < R) Update(L,R,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
void Update2(int p,int l,int r,int rt,int v)
{
    if(l == r)
    {
        addv[rt] = 0;
        maxv[rt] = v;
        return ;
    }
    PushDown(rt);
    int m = (l + r)>>1;
    if(m >= p) Update2(p,l,m,rt<<1,v);
    else Update2(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt,int limit)
{
    if(maxv[rt] < limit) return inf;
    if(l == r)
    {
        return l;
    }
    PushDown(rt);
    int m = (l + r)>>1;
    if(maxv[rt<<1|1] >= limit)
        return Query(L,R,m+1,r,rt<<1|1,limit);
    return Query(L,R,l,m,rt<<1,limit);
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,X;
        scanf("%d%d",&n,&X);
        for(int i = 1;i <= n;++i)
            scanf("%d",&a[i]);
        int ans = inf;
        int tmp;
        build(1,n,1);
        for(int i = 1;i <= n;++i)
        {
            if(a[i] >= X)
            {
                ans = 1;
                break;
            }
            Update2(i,1,n,1,a[i]);
            if(i > 1) Update(1,i-1,1,n,1,a[i]);
            int pos = Query(1,i,1,n,1,X);
            if(pos != inf)
                ans = min(ans,i - pos + 1);
        }
        if(ans == inf) ans = -1;
        printf("%d\n",ans);
    }
    return 0;
}

