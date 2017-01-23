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
int sum[maxn<<2],setf[maxn<<2];
void Pushup(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void Pushdown(int rt,int len)
{
    if(setf[rt]!=0)
    {
        sum[rt<<1|1]=(len>>1)*setf[rt];
        sum[rt<<1]=(len-(len>>1))*setf[rt];
        setf[rt<<1]=setf[rt];
        setf[rt<<1|1]=setf[rt];
        setf[rt]=0;
    }
}
void build(int l,int r,int rt)
{
    setf[rt]=0;
    if(l==r)
    {
        sum[rt]=1;
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    Pushup(rt);
}
void Update(int p,int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        setf[rt]=p;
        sum[rt]=(r-l+1)*setf[rt];
        return;
    }
    int m=(l+r)>>1;
    Pushdown(rt,r-l+1);
    if(m>=L)
    {
        Update(p,L,R,l,m,rt<<1);
    }
    if(m<R)
    {
        Update(p,L,R,m+1,r,rt<<1|1);
    }
    Pushup(rt);
}
int main()
{
    int t,n,q,tcase=0;
    int a,b,c;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d",&n);
        scanf("%d",&q);
        build(1,n,1);
        for(int i=0;i<q;++i)
        {
            scanf("%d%d%d",&a,&b,&c);
            Update(c,a,b,1,n,1);
        }
        printf("Case %d: The total value of the hook is %d.\n",tcase,sum[1]);
    }
    return 0;
}
