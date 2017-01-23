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
using namespace std;
const int maxn=10000+10;
int sum[maxn],maxv[maxn<<2],pre[maxn<<2],suff[maxn<<2];
void PushUp(int l,int r,int rt)
{
    int m=(l+r)>>1;
    maxv[rt]=max(maxv[rt<<1],maxv[rt<<1|1]);
    maxv[rt]=max(maxv[rt],pre[rt<<1|1]+suff[rt<<1]);
    pre[rt]=max(pre[rt<<1],sum[m]-sum[l-1]+pre[rt<<1|1]);
    suff[rt]=max(suff[rt<<1|1],sum[r]-sum[m]+suff[rt<<1]);
}
void build(int l,int r,int rt)
{
    if(l==r)
    {
        maxv[rt]=pre[rt]=suff[rt]=sum[r]-sum[l-1];
        return ;
    }
    int m=(l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(l,r,rt);
}
int Query(int L,int R,int l,int r,int rt,int &psum,int &pmax,int &smax)
{
    if(l>=L&&r<=R)
    {
        pmax=pre[rt];
        smax=suff[rt];
        psum=sum[r]-sum[l-1];
        return maxv[rt];
    }
    int m=(l+r)>>1;
    if(m>=R)
      return Query(L,R,l,m,rt<<1,psum,pmax,smax);
    else if(m<L)
      return Query(L,R,m+1,r,rt<<1|1,psum,pmax,smax);
    else
    {
        int s,p1,p2,su1,su2,ss1,ss2;
        s=max(Query(L,R,l,m,rt<<1,ss1,p1,su1),Query(L,R,m+1,r,rt<<1|1,ss2,p2,su2));
        s=max(s,su1+p2);
        pmax=max(p1,ss1+p2);
        smax=max(su2,ss2+su1);
        psum=ss1+ss2;
        return s;
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        sum[0]=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&sum[i]);
            sum[i]+=sum[i-1];
        }
        build(1,n,1);
        int q,x1,y1,x2,y2,l,r,ans;
        int pp,ss,pt;
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            ans=-inf;
            if(y1<x2)
            {
                ans=sum[x2]-sum[y1-1];
                l=x1;r=y1-1;
                if(l<=r)
                {
                    Query(l,r,1,n,1,pt,pp,ss);
                    if(ss>0) ans+=ss;
                }
                l=x2+1;r=y2;
                if(l<=r)
                {
                    Query(l,r,1,n,1,pt,pp,ss);
                    if(pp>0) ans+=pp;
                }
            }
            else
            {
                int tmp,p1,s1;
                l=x2;r=y1;
                ans=Query(l,r,1,n,1,pt,p1,s1);
                tmp=sum[y1]-sum[x2-1];
                l=x1;r=x2-1;
                if(l<=r)
                {
                    Query(l,r,1,n,1,pt,pp,ss);
                    tmp+=ss;
                    ans=max(ans,p1+ss);
                }
                l=y1+1;r=y2;
                if(l<=r)
                {
                    Query(l,r,1,n,1,pt,pp,ss);
                    tmp+=pp;
                    ans=max(ans,s1+pp);
                }
                ans=max(ans,tmp);
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
