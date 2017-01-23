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
#define eps 1e-8
#define pi acos(-1.0)
using namespace std;
typedef long long ll;
const int maxn = 300000+10;
const int mod = 1000000000+9;
int Fibo[maxn],A[maxn],B[maxn];
int a[maxn];
inline void Replace(int & a,int b)
{
    a = b;
    if(a >= mod) a -= mod;
}
void Init()
{
    Fibo[1] = Fibo[2] = 1;
    A[1] = B[2] = 1;
    A[2] = B[1] = 0;
    for(int i = 3; i < maxn ;++i)
    {
        Replace(Fibo[i],Fibo[i-1] + Fibo[i-2]);
        Replace(A[i],A[i-1] + A[i-2]);
        Replace(B[i],B[i-1] + B[i-2]);
    }
}
int sum[maxn<<2],fnum[maxn<<2],snum[maxn<<2];
inline void PushUp(int rt)
{
    Replace(sum[rt],sum[rt<<1] + sum[rt<<1|1]);
}
inline int F(int a,int b,int n)
{
    return ((ll)A[n]*a + (ll)B[n]*b)%mod;
}
void PushDown(int l,int r,int rt)
{
    if(fnum[rt])
    {
        int tmp,m = (l+r)>>1;
        Replace(fnum[rt<<1],fnum[rt<<1] + fnum[rt]);
        Replace(snum[rt<<1],snum[rt<<1] + snum[rt]);
        tmp = F(fnum[rt],snum[rt],m-l+3) - F(fnum[rt],snum[rt],2);
        tmp = (tmp%mod + mod)%mod;
        Replace(sum[rt<<1],sum[rt<<1] + tmp);

        int a = F(fnum[rt],snum[rt],m-l+2);
        int b = F(fnum[rt],snum[rt],m-l+3);
        Replace(fnum[rt<<1|1],fnum[rt<<1|1] + a);
        Replace(snum[rt<<1|1],snum[rt<<1|1] + b);
        tmp = F(a,b,r-m+2) - F(a,b,2);
        tmp = (tmp%mod + mod)%mod;
        Replace(sum[rt<<1|1],sum[rt<<1|1] + tmp);

        fnum[rt] = snum[rt] = 0;
    }
}
void build(int l,int r,int rt)
{
    fnum[rt] = snum[rt] = 0;
    if(l == r)
    {
        sum[rt] = a[l];
        return ;
    }
    int m = (l+r)>>1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    PushUp(rt);
}
void Update(int L,int R,int l,int r,int rt)
{
    if(l >= L && r <= R)
    {
        Replace(fnum[rt],fnum[rt] + Fibo[l-L+1]);
        Replace(snum[rt],snum[rt] + Fibo[l-L+2]);
        int tmp = (Fibo[r-L+3] - Fibo[2])%mod - (Fibo[l-L+2] - Fibo[2])%mod;
        tmp = (tmp%mod +mod)%mod;
        Replace(sum[rt],sum[rt] + tmp);
        return ;
    }
    int m = (l+r)>>1;
    PushDown(l,r,rt);
    if(m >= L) Update(L,R,l,m,rt<<1);
    if(m < R) Update(L,R,m+1,r,rt<<1|1);
    PushUp(rt);
}
int Query(int L,int R,int l,int r,int rt)
{
    if(l >= L && r <= R) return sum[rt];
    PushDown(l,r,rt);
    int m = (l+r)>>1;
    int res = 0;
    if(m >= L) res += Query(L,R,l,m,rt<<1);
    if(m < R) res += Query(L,R,m+1,r,rt<<1|1);
    if(res >= mod) res -= mod;
    return res;
}
int main()
{
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
    Init();
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= n;++i)
        scanf("%d",&a[i]);
    build(1,n,1);
    int type,l,r;
    while(m--)
    {
        scanf("%d%d%d",&type,&l,&r);
        if(type == 1) Update(l,r,1,n,1);
        else printf("%d\n",Query(l,r,1,n,1));
    }
    return 0;
}
