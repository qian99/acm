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
const int mod=1000000007;
const int maxn=40000+10;
int primes[maxn],pcnt;
bool flag[maxn];
void getprimes()
{
    memset(flag,0,sizeof(flag));
    pcnt=0;
    for(int i=2;i<maxn;++i)
    {
        if(!flag[i])
        {
            primes[pcnt++]=i;
            for(int j=i*i;j<maxn;j+=i)
                flag[j]=true;
        }
    }
}
ll pow_mod(ll x,ll n)
{
    ll res=1;
    x%=mod;
    while(n)
    {
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}
ll inv(ll x)
{
    return pow_mod(x,mod-2);
}
ll factor[110],num[110],num2[110],ans,ans2;
ll res[512][2],K;
int tot,A,C,cnt;
ll euler_phi(ll n)
{
    ll ans=n;
    for(int i=0;i<tot;++i)
        if(n%factor[i]==0)
            ans=ans-ans/factor[i];
    return ans%mod;
}
void divx(int n,bool f)
{
    int u;
    if(f) tot=0;
    for(int i=0;primes[i]*primes[i]<=n;++i)
    {
        if(n%primes[i]==0)
        {
            u=tot;
            if(!f)
            {
                for(int j=0;j<tot;++j)
                    if(primes[i]==factor[j]) {u=j;break;}
            }
            factor[u]=primes[i];
            if(u==tot) num[u]=0;
            while(n%primes[i]==0) {num[u]++;n/=primes[i];}
            if(u==tot) tot++;
        }
    }
    if(n>1)
    {
        u=tot;
        for(int j=0;j<tot;++j)
            if(n==factor[j]) {u=j;break;}
        factor[u]=n;
        if(u==tot) num[tot++]=1;
        else num[u]++;
    }
}
ll cal(ll B,ll d)  //B->B^2
{
    ll ans=0;
    if(B&1)
    {
        ans=(ans+pow_mod(d,B))%mod;
        ans=(ans+2*pow_mod(d,1+(B-1)/4))%mod;
        ans=(ans+pow_mod(d,(B-1)/2+1))%mod;
    }
    else
    {
        ans=(ans+pow_mod(d,B))%mod;
        ans=(ans+2*pow_mod(d,B/4))%mod;
        ans=(ans+pow_mod(d,B/2))%mod;
    }
    return ans*inv(4)%mod;
}
void dfs(int x,ll now)
{
    if(x==tot)
    {
        //now->B^2;
        ll d=cal(now,C);
        res[cnt][0]=d;
        res[cnt++][1]=((ll)A*A-1)/now;
        return ;
    }
    ll tmp=1;
    for(int i=0;i<=num[x];i+=2)
    {
        dfs(x+1,now*tmp);
        tmp=tmp*factor[x]*factor[x];
    }
}
void dfs2(int x,ll now,ll d)
{
    if(x==tot)
    {
        //now->循环节长度
        ans2+=pow_mod(d,now)*euler_phi(K/now)%mod;
        ans2%=mod;
        return ;
    }
    ll tmp=1;
    for(int i=0;i<=num2[x];++i)
    {
        dfs2(x+1,now*tmp,d);
        tmp*=factor[x];
    }
}
void solve()
{
    ans=0;cnt=0;
    divx(A-1,true);
    divx(A+1,false);
    dfs(0,1);
    for(int i=0;i<cnt;++i)
    {
        memset(num2,0,sizeof(num2));
        K=res[i][1];
        for(int j=0;j<tot;++j)
        {
            while(K%factor[j]==0)
            {
                num2[j]++;
                K/=factor[j];
            }
        }
        K=res[i][1];
        ans2=0;
        dfs2(0,1,res[i][0]);
        ans+=ans2*inv(K)%mod;
        ans%=mod;
    }
    ans=ans*C%mod;
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
        scanf("%d%d",&A,&C);
        if(A!=1) solve();
        else ans=C;
        printf("Case %d: %I64d\n",++tcase,ans);
    }
    return 0;
}
