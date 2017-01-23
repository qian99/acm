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
const int maxn=1000000+1000;
int primes[maxn],pcnt;
ll val[maxn],vv[maxn];
int num[maxn],cnt;
bool flag[maxn];
ll K,L,W,maxv;
void getprimes()
{
    memset(flag,0,sizeof(flag));
    for(int i=2;i<maxn;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++]=i;
            for(int j=i*2;j<maxn;j+=i)
                flag[j]=true;
        }
    }
}
void dfs(int p,ll lnow,ll mnow)
{
    if(p==cnt)
    {
        if(lnow<mnow) swap(lnow,mnow);
        if(lnow==K||mnow==1) return ;
        ll tmp=lnow-mnow;
        if(tmp>maxv)
        {
            maxv=tmp;
            L=lnow;
            W=mnow;
        }
        return ;
    }
    dfs(p+1,lnow,mnow*vv[p]);
    ll tmp=val[p];
    for(int i=1;i<num[p];++i)
    {
        dfs(p+1,lnow*tmp,mnow*vv[p]);
        tmp*=val[p];
    }
    dfs(p+1,lnow*vv[p],mnow);
}
void solve()
{
    cnt=0;
    ll tmp=K;L=W=-1;
    int i=0;
    while(tmp>1&&tmp>=primes[i]&&i<pcnt)
    {
        if(tmp%primes[i]==0)
        {
            num[cnt]=0;
            while(tmp%primes[i]==0) {tmp/=primes[i];num[cnt]++;}
            val[cnt++]=primes[i];
        }
        i++;
    }
    if(cnt==0||val[cnt-1]==K) return ;
    if(tmp!=1) {num[cnt]=1;val[cnt++]=tmp;}
    for(int i=0;i<cnt;++i)
    {
        vv[i]=val[i];
        for(int j=1;j<num[i];++j)
            vv[i]*=val[i];
    }
    maxv=-1;
    dfs(0,1,1);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprimes();
    int t,tcase=0;
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%lld",&K);
        solve();
        printf("Case %d: ",tcase);
        if(L!=-1)
            printf("%lld %lld\n",L,W);
        else
            printf("Impossible\n");
    }
    return 0;
}

