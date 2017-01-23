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
const int maxn=100000*3+10;
int res[maxn],sum[maxn<<2];
inline void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt)
{
    sum[rt]=0;
    if(l==r)
      return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
void Update(int L,int R,int l,int r,int rt,int v)
{
    if(l==r)
    {
        if(l==v||sum[rt]) return ;
        res[l]=v;
        sum[rt]=1;
        return ;
    }
    if(l>=L&&r<=R&&sum[rt]==r-l+1)
    {
        return ;
    }
    int m=(l+r)>>1;
    if(m>=L)
     Update(L,R,l,m,rt<<1,v);
    if(m<R)
     Update(L,R,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        memset(res,0,sizeof(res));
        build(1,n,1);
        int l,r,v;
        while(m--)
        {
            scanf("%d%d%d",&l,&r,&v);
            Update(l,r,1,n,1,v);
        }
        printf("%d",res[1]);
        for(int i=2;i<=n;++i)
          printf(" %d",res[i]);
        printf("\n");
    }
    return 0;
}
