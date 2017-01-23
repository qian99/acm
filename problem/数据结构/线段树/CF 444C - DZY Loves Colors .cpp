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
const int maxn = 100000+10;
ll sum[maxn<<2],addv[maxn<<2];
int color[maxn<<2];
inline void PushUp(int rt)
{
    if(color[rt<<1] == color[rt<<1|1] && color[rt<<1])
        color[rt] = color[rt<<1];
    else color[rt] = 0;
    sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}
inline void PushDown(int l, int r,int rt)
{
    if(addv[rt])
    {
        addv[rt<<1] += addv[rt];
        addv[rt<<1|1] += addv[rt];
        int m = (l+r)>>1;
        sum[rt<<1] += (m-l+1)*addv[rt];
        sum[rt<<1|1] += (r-m)*addv[rt];
        addv[rt] = 0;
    }
    if(color[rt])
    {
        color[rt<<1] = color[rt<<1|1] = color[rt];
    }
}
void build(int l,int r,int rt)
{
    sum[rt] = addv[rt] = 0;
    color[rt] = 0;
    if(l == r)
    {
        color[rt] = l;
        return ;
    }
    int m = (l + r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int L,int R,int l,int r,int rt,int v)
{
    if(l >= L && r <= R && color[rt])
    {
        addv[rt] += abs(color[rt] - v);
        sum[rt] += (ll)(r-l+1)*abs(color[rt]-v);
        color[rt] = v;
        return ;
    }
    PushDown(l,r,rt);
    int m = (l+r)>>1;
    if(m >= L) Update(L,R,l,m,rt<<1,v);
    if(m < R) Update(L,R,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
ll Query(int L,int R,int l,int r,int rt)
{
    if(l >= L && r <= R) return sum[rt];
    PushDown(l,r,rt);
    int m = (l + r) >>1;
    ll res = 0;
    if(m >= L) res += Query(L,R,l,m,rt<<1);
    if(m < R) res += Query(L,R,m+1,r,rt<<1|1);
    return res;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    int n,m,type,l,r,x;
    scanf("%d%d",&n,&m);
    build(1,n,1);
    while(m--)
    {
        scanf("%d%d%d",&type,&l,&r);
        if(type == 1)
        {
            scanf("%d",&x);
            Update(l,r,1,n,1,x);
        }
        else printf("%I64d\n",Query(l,r,1,n,1));
    }
    return 0;
}
