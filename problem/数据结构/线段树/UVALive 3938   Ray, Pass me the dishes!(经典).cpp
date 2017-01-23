#include <iostream>
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
const int maxn=500010<<1;
const int maxm=500000+10;
ll sum[maxm];
int maxsubx[maxn<<1],maxsuby[maxn<<1],maxprefix[maxn<<1],maxsuffix[maxn<<1];
void PushUp(int l,int r,int rt)
{
    int m=(l+r)>>1;
    ll maxsum=sum[maxsuby[rt<<1]]-sum[maxsubx[rt<<1]-1];
    maxsubx[rt]=maxsubx[rt<<1];
    maxsuby[rt]=maxsuby[rt<<1];
    if(maxsum<sum[maxprefix[rt<<1|1]]-sum[maxsuffix[rt<<1]-1])
    {
        maxsum=sum[maxprefix[rt<<1|1]]-sum[maxsuffix[rt<<1]-1];
        maxsubx[rt]=maxsuffix[rt<<1];
        maxsuby[rt]=maxprefix[rt<<1|1];
    }
    if(maxsum<sum[maxsuby[rt<<1|1]]-sum[maxsubx[rt<<1|1]-1])
    {
        maxsum=sum[maxsuby[rt<<1|1]]-sum[maxsubx[rt<<1|1]-1];
        maxsubx[rt]=maxsubx[rt<<1|1];
        maxsuby[rt]=maxsuby[rt<<1|1];
    }
    maxsum=sum[maxprefix[rt<<1]]-sum[l-1];
    maxprefix[rt]=maxprefix[rt<<1];
    if(maxsum<sum[maxprefix[rt<<1|1]]-sum[l-1])
    {
        maxsum=sum[maxprefix[rt<<1|1]]-sum[l-1];
        maxprefix[rt]=maxprefix[rt<<1|1];
    }
    maxsum=sum[r]-sum[maxsuffix[rt<<1]-1];
    maxsuffix[rt]=maxsuffix[rt<<1];
    if(maxsum<sum[r]-sum[maxsuffix[rt<<1|1]-1])
    {
        maxsuffix[rt]=maxsuffix[rt<<1|1];
    }
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        maxsubx[rt]=maxsuby[rt]=l;
        maxprefix[rt]=maxsuffix[rt]=l;
        return;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(l,r,rt);
}
void Query(int L,int R,int l,int r,int rt,int &x,int &y,int &pre,int &suf)
{
    if(l>=L&&r<=R)
    {
        x=maxsubx[rt];
        y=maxsuby[rt];
        pre=maxprefix[rt];
        suf=maxsuffix[rt];
        return;
    }
    int xa,ya,xb,yb,pa,sa,pb,sb;
    int m=(l+r)>>1;
    if(m>=L&&m<R)
    {
        Query(L,R,l,m,rt<<1,xa,ya,pa,sa);
        Query(L,R,m+1,r,rt<<1|1,xb,yb,pb,sb);
        ll maxsum=sum[ya]-sum[xa-1];
        x=xa;y=ya;
        if(maxsum<sum[pb]-sum[sa-1])
        {
            maxsum=sum[pb]-sum[sa-1];
            x=sa;
            y=pb;
        }
        if(maxsum<sum[yb]-sum[xb-1])
        {
            maxsum=sum[yb]-sum[xb-1];
            x=xb;
            y=yb;
        }
        maxsum=sum[pa]-sum[L-1];
        pre=pa;
        if(maxsum<sum[pb]-sum[L-1])
        {
            pre=pb;
        }
        maxsum=sum[R]-sum[sa-1];
        suf=sa;
        if(maxsum<sum[R]-sum[sb-1])
        {
            suf=sb;
        }
        return;
    }
    if(m>=L)
    {
        Query(L,R,l,m,rt<<1,xa,ya,pa,sa);
        x=xa;
        y=ya;
        pre=pa;
        suf=sa;
    }
    else if(m<R)
    {
        Query(L,R,m+1,r,rt<<1|1,xb,yb,pb,sb);
        x=xb;
        y=yb;
        pre=pb;
        suf=sb;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int n,m;
    int tcase=0;
    while(~scanf("%d%d",&n,&m))
    {
        tcase++;
        sum[0]=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&sum[i]);
            sum[i]+=sum[i-1];
        }
        build(1,n,1);
        printf("Case %d:\n",tcase);
        int l,r,x,y,p,s;
        for(int i=0;i<m;++i)
        {
            scanf("%d%d",&l,&r);
            Query(l,r,1,n,1,x,y,p,s);
            printf("%d %d\n",x,y);
        }
    }
    return 0;
}
