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
ll sum[maxn<<2],counts[maxn<<2];
ll num[maxn];
inline void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    counts[rt]=counts[rt<<1]+counts[rt<<1|1];
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        sum[rt]=num[l];
        counts[rt]=sum[rt]==1?0:1;
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
void Update(int L,int R,int l,int r,int rt)
{
    if(counts[rt]==0) return;
    if(l==r)
    {
        sum[rt]=(ll)sqrt((double)sum[rt]);
        if(sum[rt]==1) counts[rt]=0;
        return ;
    }
    int m=(l+r)>>1;
    if(m>=L)
      Update(L,R,l,m,rt<<1);
    if(m<R)
      Update(L,R,m+1,r,rt<<1|1);
    PushUp(rt);
}
ll Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
      return sum[rt];
    int m=(l+r)>>1;
    ll res=0;
    if(m>=L)
      res+=Query(L,R,l,m,rt<<1);
    if(m<R)
      res+=Query(L,R,m+1,r,rt<<1|1);
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    int tcase=0;
    while(~scanf("%d",&n))
    {
        tcase++;
        for(int i=1;i<=n;++i)
          scanf("%lld",&num[i]);
        build(1,n,1);
        int q,k,l,r;
        printf("Case #%d:\n",tcase);
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d%d%d",&k,&l,&r);
            if(l>r) swap(l,r);
            if(k==0)
              Update(l,r,1,n,1);
            else
              printf("%lld\n",Query(l,r,1,n,1));
        }
        printf("\n");
    }
    return 0;
}
