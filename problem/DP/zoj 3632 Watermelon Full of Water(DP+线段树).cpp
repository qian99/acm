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
#define eps 1e-9
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=500000+10;
ll minv[maxn<<2],setv[maxn<<2];
ll dp[maxn][2],val[maxn],days[maxn];
void PushUp(int rt)
{
    minv[rt]=min(minv[rt<<1],minv[rt<<1|1]);
}
void PushDown(int rt)
{
    if(setv[rt]!=-1)
    {
        if(setv[rt<<1]!=-1) setv[rt<<1]=min(setv[rt<<1],setv[rt]);
        else setv[rt<<1]=setv[rt];
        if(setv[rt<<1|1]!=-1) setv[rt<<1|1]=min(setv[rt<<1|1],setv[rt]);
        else setv[rt<<1|1]=setv[rt];
        minv[rt<<1]=min(minv[rt<<1],setv[rt]);
        minv[rt<<1|1]=min(minv[rt<<1|1],setv[rt]);
        setv[rt]=-1;
    }
}
void build(int l,int r,int rt)
{
    minv[rt]=Inf;setv[rt]=-1;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
ll Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)
    {
        return minv[rt];
    }
    int m=(l+r)>>1;
    PushDown(rt);
    ll ans=Inf;
    if(m>=L) ans=min(ans,Query(L,R,l,m,rt<<1));
    if(m<R) ans=min(ans,Query(L,R,m+1,r,rt<<1|1));
    return ans;
}
void Update(int L,int R,int l,int r,int rt,ll v)
{
    if(l>=L&&r<=R)
    {
        if(setv[rt]!=-1) setv[rt]=min(setv[rt],v);
        else setv[rt]=v;
        minv[rt]=min(minv[rt],v);
        return ;
    }
    PushDown(rt);
    int m=(l+r)>>1;
    if(m>=L) Update(L,R,l,m,rt<<1,v);
    if(m<R) Update(L,R,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n;
    while(~scanf("%d",&n))
    {
        build(1,n,1);
        for(int i=1;i<=n;++i)
            scanf("%lld",&val[i]);
        for(int i=1;i<=n;++i)
            scanf("%lld",&days[i]);
        dp[1][0]=Inf;dp[1][1]=val[1];
        Update(1,min((ll)n,days[1]),1,n,1,val[1]);
        for(int i=2;i<=n;++i)
        {
            dp[i][1]=min(dp[i-1][0],dp[i-1][1])+val[i];
            dp[i][0]=Query(i,i,1,n,1);
            Update(i,min((ll)n,i+days[i]-1),1,n,1,dp[i][1]);
        }
        printf("%lld\n",min(dp[n][0],dp[n][1]));
    }
    return 0;
}
