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
const int maxn=1000000+10;
int primes[maxn],pcnt;
bool flag[maxn];
void getprimes()
{
    memset(flag,0,sizeof(flag));
    pcnt=0;
    for(ll i=2;i<maxn;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++]=i;
            for(ll j=i*i;j<maxn;j+=i)
                flag[j]=true;
        }
    }
}
ll fac[111];
int num[111];
int fcnt;
void cal(ll n)
{
    fcnt=0;
    int i=0;
    for(i=0;i<pcnt&&((ll)primes[i]*primes[i]<=n);i++)
    {
        if(n%primes[i]==0)
        {
            fac[fcnt]=primes[i];
            num[fcnt]=0;
            while(n%primes[i]==0)
            {
                num[fcnt]++;
                n/=primes[i];
            }
            fcnt++;
        }
    }
    if(n>1) {fac[fcnt]=n;num[fcnt++]=1;}
}
ll factor[15111];
int tot;
void finds(int pos,ll now)
{
    if(pos==fcnt)
    {
        factor[tot++]=now;
        return ;
    }
    ll tmp=1;
    for(int i=0;i<=num[pos];++i)
    {
        finds(pos+1,now*tmp);
        tmp*=fac[pos];
    }
}
void Init(ll n)
{
    getprimes();
    cal(n);
    tot=0;
    finds(0,1);
    sort(factor,factor+tot);
}
ll ans[100010];
int cnt;
void dfs(int x,ll k)
{
    if(k==0)
    {
        ans[cnt++]=factor[x];
        if(cnt>100000) return ;
        return ;
    }
    if(x==0)
    {
        ans[cnt++]=1;
        return ;
    }
    if(cnt>100000) return ;
    for(int i=0;i<=x;++i)
    {
        if(factor[x]%factor[i]==0)
            dfs(i,k-1);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    ll n,k;
    scanf("%I64d%I64d",&n,&k);
    cnt=0;
    Init(n);
    dfs(tot-1,k);
    cnt=min(cnt,100000);
    for(int i=0;i<cnt;++i)
    {
        if(i) printf(" ");
        printf("%I64d",ans[i]);
    }
    printf("\n");
    return 0;
}
