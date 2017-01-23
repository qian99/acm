#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<queue>
#include<set>
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
ll sum[maxn<<2];
int fone[maxn<<2];
void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    fone[rt]=fone[rt<<1]+fone[rt<<1|1];
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        scanf("%I64d",&sum[rt]);
        fone[rt]=(sum[rt]==1)?1:0;
        if(sum[rt]==0) fone[rt]=1;
        return;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
void Update(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R&&fone[rt]==r-l+1)
    {
        return;
    }
    if(l==r)
    {
        sum[rt]=(ll)sqrt((double)sum[rt]);
        if(sum[rt]==1) fone[rt]=1;
        return;
    }
    int m=(l+r)>>1;
    if(m>=L&&fone[rt<<1]!=m-l+1)
     Update(L,R,l,m,rt<<1);
    if(m<R&&fone[rt<<1|1]!=r-m)
     Update(L,R,m+1,r,rt<<1|1);
    PushUp(rt);
}
ll Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        return sum[rt];
    }
    int m=(l+r)>>1;
    ll s=0;
    if(m>=L)
      s+=Query(L,R,l,m,rt<<1);
    if(m<R)
      s+=Query(L,R,m+1,r,rt<<1|1);
    return s;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    int tcase=0;
    while(~scanf("%d",&n))
    {
        tcase++;
        build(1,n,1);
        printf("Case #%d:\n",tcase);
        scanf("%d",&m);
        while(m--)
        {
            int T,x,y;
            scanf("%d%d%d",&T,&x,&y);
            if(x>y) swap(x,y);
            if(T==0)
              Update(x,y,1,n,1);
            else
            {
                ll ans=Query(x,y,1,n,1);
                printf("%I64d\n",ans);
            }
        }
        printf("\n");
    }
    return 0;
}
