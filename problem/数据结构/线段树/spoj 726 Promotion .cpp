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
const int maxn=1000000+10;
int sum[maxn<<2];
void build(int l,int r,int rt)
{
    sum[rt]=0;
    if(l==r) return ;
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
}
inline void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
int Query(int l,int r,int rt,int type)
{
    if(l==r)
    {
        sum[rt]--;
        return l;
    }
    int m=(l+r)>>1;
    int res;
    if(type)
    {
        if(sum[rt<<1|1]>0) res=Query(m+1,r,rt<<1|1,type);
        else res=Query(l,m,rt<<1,type);
    }
    else
    {
        if(sum[rt<<1]>0) res=Query(l,m,rt<<1,type);
        else res=Query(m+1,r,rt<<1|1,type);
    }
    PushUp(rt);
    return res;
}
void Update(int p,int l,int r,int rt)
{
    if(l==r)
    {
        sum[rt]++;
        return ;
    }
    int m=(l+r)>>1;
    if(m>=p) Update(p,l,m,rt<<1);
    else Update(p,m+1,r,rt<<1|1);
    PushUp(rt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,N=1e6;
    ll ans=0;
    build(1,N,1);
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        int k,v;
        scanf("%d",&k);
        while(k--)
        {
            scanf("%d",&v);
            Update(v,1,N,1);
        }
//        cout<<Query(1,N,1,1)<<endl;
//        cout<<Query(1,N,1,0)<<endl;
        ans+=Query(1,N,1,1)-Query(1,N,1,0);
    }
    printf("%lld\n",ans);
    return 0;
}
