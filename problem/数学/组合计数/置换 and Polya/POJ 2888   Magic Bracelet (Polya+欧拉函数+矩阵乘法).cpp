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
const int mod=9973;
const int maxn=40000+10;
struct Matrix
{
    int mat[11][11],size;
    void Init(int size)
    {
        this->size=size;
        for(int i=0;i<size;++i)
            for(int j=0;j<size;++j)
                mat[i][j]=(i==j);
    }
    void clear() {memset(mat,0,sizeof(mat));}
}mx;
Matrix operator *(const Matrix &a,const Matrix &b)
{
    Matrix c;c.clear();
    c.size=a.size;
    for(int k=0;k<c.size;++k)
        for(int i=0;i<c.size;++i)
            for(int j=0;j<c.size;++j)
                c.mat[i][j]=(c.mat[i][j]+a.mat[i][k]*b.mat[k][j])%mod;
    return c;
}
Matrix pow_mat(Matrix a,int n)
{
    Matrix res;
    res.Init(a.size);
    while(n)
    {
        if(n&1) res=res*a;
        a=a*a;
        n>>=1;
    }
    return res;
}
int pow_mod(int x,int n)
{
    int res=1;
    x%=mod;
    while(n)
    {
        if(n&1) res=res*x%mod;
        x=x*x%mod;
        n>>=1;
    }
    return res;
}
int inv(int a)
{
    return pow_mod(a,mod-2)%mod;
}
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
int euler_phi(int n)
{
    int ans=n;
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
int factor[110],num[110],tot,ans;
void dfs(int x,int now,int n)
{
    if(x==tot)
    {
        int val=0;
        Matrix y=pow_mat(mx,now);
        for(int i=0;i<mx.size;++i)
            val=(val+y.mat[i][i])%mod;
        ans=(ans+euler_phi(n/now)*val)%mod;
        return ;
    }
    int tmp=1;
    for(int i=0;i<=num[x];++i)
    {
        dfs(x+1,now*tmp,n);
        tmp*=factor[x];
    }
}
void solve(int n)
{
    ans=0;tot=0;
    int N=n;
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
    dfs(0,1,n);
    ans=ans*inv(n)%mod;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprimes();
    int t,n,m,k;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&k);
        mx.size=m;
        mx.clear();
        for(int i=0;i<mx.size;++i)
            for(int j=0;j<mx.size;++j)
                mx.mat[i][j]=1;
        int u,v;
        while(k--)
        {
            scanf("%d%d",&u,&v);
            mx.mat[u-1][v-1]=0;
            mx.mat[v-1][u-1]=0;
        }
        solve(n);
        printf("%d\n",ans);
    }
    return 0;
}
