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
const int maxn=100000+10;
int val[maxn],n,M,p,T;
ll sum[maxn];
ll cal(int l,int r,int times)
{
    if(times<=0) return 0;
    ll maxv=0,tmp;
    int t;
    for(int i=r;i<=n;++i)
    {
        if(i-r<=times)
        {
            tmp=sum[i]-sum[r];
            t=times-(i-r);
            if(i-M-l<t)
            {
                t-=(i-M-l);
                tmp+=sum[l-1]-sum[max(0,l-t-1)];
            }
            maxv=max(maxv,tmp);
        }
        else break;
    }
    for(int i=l;i>=1;--i)
    {
        if(l-i<=times)
        {
            tmp=sum[l-1]-sum[i-1];
            t=times-(l-i);
            if(r-i-M<t)
            {
                t-=(r-i-M);
                tmp+=sum[min(n,r+t)]-sum[r];
            }
            maxv=max(maxv,tmp);
        }
        else break;
    }
    return maxv;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&p))
    {
        for(int i=1;i<=n;++i)
            scanf("%d",&val[i]);
        sum[0]=0;
        for(int i=1;i<=n;++i)
            sum[i]=sum[i-1]+val[i];
        scanf("%d%d",&M,&T);
        int l=p,r=p;
        ll ans=val[p];
        while((l>1&&r<n)&&(r-l+2)<=M&&T>0)
        {
            ans+=val[--l];
            ans+=val[++r];
            T--;
        }
        if(T>0)
        {
            int L=l,R=r,t=T;
            ll tmp=0,maxv=0;
            while(R<n&&(R-l+1)<=M&&t>0)
            {
                tmp+=val[++R];
                t--;
            }
            if(R-l==M)
                maxv=cal(l,R,t)+tmp;
            else maxv=tmp;
            tmp=0;t=T;
            while(L>1&&(r-L+1)<=M&&t>0)
            {
                tmp+=val[--L];
                t--;
            }
            if(r-L==M)
                maxv=max(maxv,cal(L,r,t)+tmp);
            else maxv=max(maxv,tmp);
            ans+=maxv;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
