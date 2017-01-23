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
#include<bitset>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=100000+10;
ll sum[maxn<<2],maxv[maxn<<2];
int a[maxn];
void PushUp(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
    maxv[rt]=max(maxv[rt<<1],maxv[rt<<1|1]);
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        sum[rt]=maxv[rt]=a[l];
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
ll Query(int L,int R,int l,int r,int rt)
{
    if(l>=L&&r<=R)  return sum[rt];
    int m=(l+r)>>1;
    ll res=0;
    if(m>=L) res+=Query(L,R,l,m,rt<<1);
    if(m<R) res+=Query(L,R,m+1,r,rt<<1|1);
    return res;
}
void Modulo(int L,int R,int l,int r,int rt,int mod)
{
    if(maxv[rt]<mod) return ;
    if(l==r)
    {
        sum[rt]%=mod;
        maxv[rt]=sum[rt];
        return ;
    }
    int m=(l+r)>>1;
    if(m>=L) Modulo(L,R,l,m,rt<<1,mod);
    if(m<R) Modulo(L,R,m+1,r,rt<<1|1,mod);
    PushUp(rt);
}
void Update(int p,int l,int r,int rt,int v)
{
    if(l==r)
    {
        sum[rt]=maxv[rt]=v;
        return ;
    }
    int m=(l+r)>>1;
    if(m>=p) Update(p,l,m,rt<<1,v);
    else Update(p,m+1,r,rt<<1|1,v);
    PushUp(rt);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    build(1,n,1);
    int l,r,x,type;
    while(m--)
    {
        scanf("%d",&type);
        if(type==1)
        {
            scanf("%d%d",&l,&r);
            printf("%I64d\n",Query(l,r,1,n,1));
        }
        else if(type==2)
        {
            scanf("%d%d%d",&l,&r,&x);
            Modulo(l,r,1,n,1,x);
        }
        else
        {
            scanf("%d%d",&l,&x);
            Update(l,1,n,1,x);
        }
    }
    return 0;
}