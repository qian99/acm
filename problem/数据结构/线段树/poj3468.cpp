#include <iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<cmath>
#include<vector>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
const int maxn=100000+10;
__int64 sum[maxn<<2],setf[maxn<<2];
void Pushup(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void Pushdown(int rt,int len)
{
    if(setf[rt]!=0)
    {
        setf[rt<<1]+=setf[rt];
        setf[rt<<1|1]+=setf[rt];
        sum[rt<<1]+=setf[rt]*(len-(len>>1));
        sum[rt<<1|1]+=setf[rt]*(len>>1);
        setf[rt]=0;
    }
}
void build(int l,int r,int rt)
{
    setf[rt]=0;
    if(l==r)
    {
        scanf("%I64d",&sum[rt]);
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    Pushup(rt);
}
__int64 Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        return sum[rt];
    }
    int m=(l+r)>>1;
    Pushdown(rt,r-l+1);
    __int64 u=0;
    if(m>=L)
      u+=Query(L,R,l,m,rt<<1);
    if(m<R)
      u+=Query(L,R,m+1,r,rt<<1|1);
    return u;
}
void Update(int p,int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        setf[rt]+=p;
        sum[rt]+=(__int64)p*(r-l+1);
        return ;
    }
    int m=(r+l)>>1;
    Pushdown(rt,r-l+1);
    if(m>=L)
      Update(p,L,R,l,m,rt<<1);
    if(m<R)
      Update(p,L,R,m+1,r,rt<<1|1);
    Pushup(rt);
}
int main()
{
    int n,q,a,b,d;
    char c[2];
    while(~scanf("%d%d",&n,&q))
    {
        build(1,n,1);
        for(int i=0;i<q;++i)
        {
            scanf("%s",c);
            if(c[0]=='Q')
            {
                scanf("%d%d",&a,&b);
                printf("%I64d\n",Query(a,b,1,n,1));
            }
            else
            {
                scanf("%d%d%d",&a,&b,&d);
                Update(d,a,b,1,n,1);
            }
        }
    }
    return 0;
}