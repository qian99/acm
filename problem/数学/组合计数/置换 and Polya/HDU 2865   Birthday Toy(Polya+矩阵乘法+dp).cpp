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
//矩阵乘法相关
struct Matrix
{
    ll mat[2][2];
    void Init()
    {
        mat[0][0]=mat[1][1]=1;
        mat[1][0]=mat[0][1]=0;
    }
    void clear() {memset(mat,0,sizeof(mat));}
}mx;
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c;c.clear();
    for(int k=0;k<2;++k)
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mod;
    return c;
}
Matrix pow_mat(Matrix x,ll n)
{
    Matrix res;res.Init();
    while(n)
    {
        if(n&1) res=res*x;
        x=x*x;
        n>>=1;
    }
    return res;
}
//数论相关
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
ll euler_phi(ll n)
{
    ll ans=n;
    for(int i=0;primes[i]*primes[i]<=n;++i)
    {
        if(n%primes[i]==0)
        {
            ans=ans-ans/primes[i];
            while(n%primes[i]==0) n/=primes[i];
        }
    }
    if(n>1) ans=ans-ans/n;
    return ans%mod;
}
ll pow_mod(ll x,ll n)
{
    ll res=1;
    while(n)
    {
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}
ll inv(ll a)
{
    return pow_mod(a,mod-2);
}
int n,k;
ll ans;
int factor[110],num[110],tot;
void dfs(int x,int now)
{
    if(x==tot)
    {
        if(now==1) return ;
        Matrix y=pow_mat(mx,now-1);
        ans+=y.mat[1][0]*euler_phi(n/now);
        ans%=mod;
        return ;
    }
    int tmp=1;
    for(int i=0;i<=num[x];++i)
    {
        dfs(x+1,now*tmp);
        tmp*=factor[x];
    }
}
void solve()
{
    int N=n;
    tot=0;
    for(int i=0;primes[i]*primes[i]<=N;++i)
    {
        if(N%primes[i]==0)
        {
            factor[tot]=primes[i];
            num[tot]=0;
            while(N%primes[i]==0) {num[tot]++;N/=primes[i];}
            tot++;
        }
    }
    if(N>1) {factor[tot]=N;num[tot++]=1;}
    mx.clear();
    mx.mat[0][0]=k-3;mx.mat[1][0]=k-2;
    mx.mat[0][1]=1;mx.mat[1][1]=0;
    dfs(0,1);
    ans=ans*(k-1)%mod;
    ans=ans*k%mod;
    ans=ans*inv(n)%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprimes();
    while(~scanf("%d%d",&n,&k))
    {
        ans=0;
        solve();
        printf("%I64d\n",ans);
    }
    return 0;
}
