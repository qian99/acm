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
#include<set>
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define eps 1e-6
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn=1000000+10;
struct Matrix
{
    ll mat[2][2];
    void clear() {memset(mat,0,sizeof(mat));}
    void Init() {mat[0][0]=mat[1][1]=1;mat[1][0]=mat[0][1]=0;}
};
Matrix Mul_mat(const Matrix &a,const Matrix &b,ll mod)
{
    Matrix c;
    c.clear();
    for(int k=0;k<2;++k)
        for(int i=0;i<2;++i)
            for(int j=0;j<2;++j)
            {
                c.mat[i][j]+=a.mat[i][k]*b.mat[k][j]%mod;
                if(c.mat[i][j]>=mod) c.mat[i][j]-=mod;
            }
    return c;
}
Matrix pow_mat(Matrix a,ll n,ll mod)
{
    Matrix res;
    res.Init();
    while(n)
    {
        if(n&1) res=Mul_mat(res,a,mod);
        a=Mul_mat(a,a,mod);
        n>>=1;
    }
    return res;
}
ll pow_mod(ll x,ll n,ll mod)
{
    ll res=1;
    while(n)
    {
        if(n&1) res=res*x%mod;
        n>>=1;
        x=x*x%mod;
    }
    return res;
}
ll gcd(ll a,ll b) {return b==0?a:gcd(b,a%b);}
ll lcm(ll a,ll b) {return a/gcd(a,b)*b;}
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
            for(ll j=(ll)i*i;j<maxn;j+=i)
                flag[j]=true;
        }
    }
}
ll factor[111],num[111],facnt;
void getFactor(ll x)
{
    facnt=0;
    for(int i=0;primes[i]<=x/primes[i];++i)
    {
        if(x%primes[i]==0)
        {
            num[facnt]=0;
            factor[facnt]=primes[i];
            while(x%primes[i]==0) {x/=primes[i];num[facnt]++;}
            facnt++;
        }
    }
    if(x>1) {factor[facnt]=x;num[facnt++]=1;}
}
//勒让德符号
int legendre(ll a,ll p)
{
    if(pow_mod(a,(p-1)>>1,p)==1) return 1;
    return -1;
}
int F0=1,F1=1;
ll getFib(ll n,ll mod)
{
    if(n==0) return F0%mod;
    if(n==1) return F1%mod;
    Matrix x;
    x.mat[0][0]=x.mat[1][0]=x.mat[0][1]=1;
    x.mat[1][1]=0;
    x=pow_mat(x,n-1,mod);
    return (x.mat[0][0]*F0+x.mat[1][0]*F1)%mod;
}
ll fac[maxn];
ll G[maxn];  //记忆答案，最开始赋值为-1
ll cal(ll p)
{
    if(p<maxn&&G[p]!=-1) return G[p];
    ll x;
    if(legendre(5,p)==1) x=p-1;
    else x=2*(p+1);
    int cnt=0;
    for(ll i=1;i*i<=x;++i)
    {
        if(x%i==0)
        {
            fac[cnt++]=i;
            if(i*i!=x) fac[cnt++]=x/i;
        }
    }
    sort(fac,fac+cnt);
    ll res;
    for(int i=0;i<cnt;++i)
    {
        if(getFib(fac[i],p)==F0&&getFib(fac[i]+1,p)==F1)
        {
            res=fac[i];
            break;
        }
    }
    if(p<maxn) G[p]=res;
    return res;
}
ll find_loop(ll n)
{
    getFactor(n);
    ll ans=1;
    for(int i=0;i<facnt;++i)
    {
        ll record=1;
        if(factor[i]==2) record=3;
        else if(factor[i]==3) record=8;
        else if(factor[i]==5) record=20;
        else record=cal(factor[i]);
        for(int j=1;j<num[i];++j)
            record*=factor[i];
        ans=lcm(ans,record);
    }
    return ans;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprimes();
    memset(G,0xff,sizeof(G));
    int t;
    int n,p;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&p);
        ll mod1=p;
        ll mod2=find_loop(mod1);
        ll mod3=find_loop(mod2);
        ll res=getFib(n,mod3);
        res=getFib(res,mod2);
        res=getFib(res,mod1);
        printf("%d\n",(int)res);
    }
    return 0;
}
