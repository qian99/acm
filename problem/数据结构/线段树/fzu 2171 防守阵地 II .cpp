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
ll sum[maxn<<2],addv[maxn<<2];
int num[maxn];
void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void PushDown(int l,int r,int rt)
{
    if(addv[rt])
    {
        int m=(l+r)>>1;
        addv[rt<<1]+=addv[rt];
        addv[rt<<1|1]+=addv[rt];
        sum[rt<<1]+=(m-l+1)*addv[rt];
        sum[rt<<1|1]+=(r-m)*addv[rt];
        addv[rt]=0;
    }
}
void build(int l,int r,int rt)
{
    addv[rt]=0;
    if(l==r)
    {
        sum[rt]=num[l];
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
void Update(int L,int R,int l,int r,int rt,int v)
{
    if(l>=L&&r<=R)
    {
        addv[rt]+=v;
        sum[rt]+=(r-l+1)*v;
        return ;
    }
    int m=(l+r)>>1;
    PushDown(l,r,rt);
    if(m>=L) Update(L,R,l,m,rt<<1,v);
    if(m<R) Update(L,R,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
ll Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        return sum[rt];
    }
    PushDown(l,r,rt);
    ll res=0;
    int m=(l+r)>>1;
    if(m>=L) res+=Query(L,R,l,m,rt<<1);
    if(m<R) res+=Query(L,R,m+1,r,rt<<1|1);
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m,q;
    while(~scanf("%d%d%d",&n,&m,&q))
    {
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&num[i]);
        }
        build(1,n,1);
        int lsq=0,now;
        while(q--)
        {
            scanf("%d",&now);
            if(lsq)
            {
                Update(lsq,lsq+m-1,1,n,1,-1);
            }
            ll ans=Query(now,now+m-1,1,n,1);
            printf("%lld\n",ans);
            lsq=now;
        }
    }
    return 0;
}
