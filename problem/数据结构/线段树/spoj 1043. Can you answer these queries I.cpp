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
const int maxn=50000+10;
int sum[maxn],maxv[maxn<<2],pre[maxn<<2],suff[maxn<<2];
inline void PushUp(int l,int r,int rt)
{
    int m=(l+r)>>1;
    int ls=rt<<1,rs=rt<<1|1;
    maxv[rt]=max(maxv[ls],maxv[rs]);
    maxv[rt]=max(maxv[rt],suff[ls]+pre[rs]);
    pre[rt]=max(sum[m]-sum[l-1]+pre[rs],pre[ls]);
    suff[rt]=max(sum[r]-sum[m]+suff[ls],suff[rs]);
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        maxv[rt]=pre[rt]=suff[rt]=sum[l]-sum[l-1];
        return;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(l,r,rt);
}
int Query(int L,int R,int l,int r,int rt,int &ps,int &lsum,int &rsum)
{
    if(l>=L&&r<=R)
    {
        lsum=pre[rt];rsum=suff[rt];
        ps=sum[r]-sum[l-1];
        return maxv[rt];
    }
    int m=(l+r)>>1;
    int ls=rt<<1,rs=rt<<1|1;
    if(R<=m)
     return Query(L,R,l,m,ls,ps,lsum,rsum);
    else if(L>m)
     return Query(L,R,m+1,r,rs,ps,lsum,rsum);
    else
    {
        int ltmp1,rtmp1,ltmp2,rtmp2,s,ps1,ps2;
        int s1=Query(L,R,l,m,ls,ps1,ltmp1,rtmp1);
        int s2=Query(L,R,m+1,r,rs,ps2,ltmp2,rtmp2);
        s=max(s1,s2);
        s=max(s,rtmp1+ltmp2);
        lsum=max(ltmp1,ps1+ltmp2);
        rsum=max(rtmp2,ps2+rtmp1);
        ps=ps1+ps2;
        return s;
    }
}
int main()
{
    //freopen("a.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,q;
    while(~scanf("%d",&n))
    {
        sum[0]=0;
        int a;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a);
            sum[i]=sum[i-1]+a;
        }
        build(1,n,1);
        scanf("%d",&q);
        int l,r,tm1,tm2,tm3;
        while(q--)
        {
            scanf("%d%d",&l,&r);
            printf("%d\n",Query(l,r,1,n,1,tm1,tm2,tm3));
        }
    }
    return 0;
}
