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
int sum[maxn<<2],maxv[maxn<<2],pre[maxn<<2],suff[maxn<<2];
int num[maxn];
inline void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    maxv[rt]=max(maxv[rt<<1],maxv[rt<<1|1]);
    maxv[rt]=max(maxv[rt],suff[rt<<1]+pre[rt<<1|1]);
    pre[rt]=max(pre[rt<<1],sum[rt<<1]+pre[rt<<1|1]);
    suff[rt]=max(suff[rt<<1|1],sum[rt<<1|1]+suff[rt<<1]);
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        sum[rt]=maxv[rt]=pre[rt]=suff[rt]=num[l];
        return;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt,int &tsum,int & maxp,int & maxs)
{
    if(l>=L&&r<=R)
    {
        maxp=pre[rt];
        maxs=suff[rt];
        tsum=sum[rt];
        return maxv[rt];
    }
    int m=(l+r)>>1;
    if(m>=R)
      return Query(L,R,l,m,rt<<1,tsum,maxp,maxs);
    else if(m<L)
      return Query(L,R,m+1,r,rt<<1|1,tsum,maxp,maxs);
    else
    {
        int tos,s1,s2,p1,p2,su1,su2;
        tos=max(Query(L,R,l,m,rt<<1,s1,p1,su1),Query(L,R,m+1,r,rt<<1|1,s2,p2,su2));
        tos=max(tos,su1+p2);
        maxp=max(p1,s1+p2);
        maxs=max(su2,s2+su1);
        tsum=s1+s2;
        return tos;
    }
}
void Update(int p,int l,int r,int rt,int v)
{
    if(l==r)
    {
        sum[rt]=maxv[rt]=pre[rt]=suff[rt]=v;
        return;
    }
    int m=(l+r)>>1;
    if(p<=m)
      Update(p,l,m,rt<<1,v);
    else
      Update(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=n;++i)
            scanf("%d",&num[i]);
        build(1,n,1);
        int q,k,x,y,t1,t2,t3;
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d%d%d",&k,&x,&y);
            if(k==0)
              Update(x,1,n,1,y);
            else
              printf("%d\n",Query(x,y,1,n,1,t1,t2,t3));
        }
    }
    return 0;
}
