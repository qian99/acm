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
int num[maxn];
struct SegTree
{
    int sum[maxn<<2],pre[maxn<<2],suff[maxn<<2];
    ll val[maxn<<2];
    int bitp;
    void PushUp(int l,int r,int rt)
    {
        int m=(l+r)>>1;
        sum[rt]=sum[rt<<1]+sum[rt<<1|1];
        if(sum[rt<<1]==m-l+1)
            pre[rt]=sum[rt<<1]+pre[rt<<1|1];
        else pre[rt]=pre[rt<<1];
        if(sum[rt<<1|1]==r-m)
            suff[rt]=suff[rt<<1]+sum[rt<<1|1];
        else
            suff[rt]=suff[rt<<1|1];
        if(suff[rt<<1]&&pre[rt<<1|1])
        {
            val[rt]=val[rt<<1]+val[rt<<1|1];
            ll tmp=suff[rt<<1];
            val[rt]-=tmp*(tmp+1)/2;
            tmp=pre[rt<<1|1];
            val[rt]-=tmp*(tmp+1)/2;
            tmp=suff[rt<<1]+pre[rt<<1|1];
            val[rt]+=tmp*(tmp+1)/2;
        }
        else
            val[rt]=val[rt<<1]+val[rt<<1|1];
    }
    void build(int l,int r,int rt)
    {
        if(l==r)
        {
            val[rt]=sum[rt]=pre[rt]=suff[rt]=(num[l]>>bitp)&1;
            return ;
        }
        int m=(l+r)>>1;
        build(l,m,rt<<1);
        build(m+1,r,rt<<1|1);
        PushUp(l,r,rt);
    }
    void Update(int p,int l,int r,int rt,int v)
    {
        if(l==r)
        {
            sum[rt]=val[rt]=pre[rt]=suff[rt]=v;
            return ;
        }
        int m=(l+r)>>1;
        if(m>=p) Update(p,l,m,rt<<1,v);
        else Update(p,m+1,r,rt<<1|1,v);
        PushUp(l,r,rt);
    }
}tree[17];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
        scanf("%d",&num[i]);
    for(int i=0;i<17;++i)
    {
        tree[i].bitp=i;
        tree[i].build(1,n,1);
    }
    int p,v;
    ll sum;
    while(m--)
    {
        scanf("%d%d",&p,&v);
        sum=0;
        for(int i=0;i<17;++i)
        {
            tree[i].Update(p,1,n,1,(v>>i)&1);
            sum+=(1<<i)*tree[i].val[1];
        }
        printf("%I64d\n",sum);
    }
    return 0;
}
