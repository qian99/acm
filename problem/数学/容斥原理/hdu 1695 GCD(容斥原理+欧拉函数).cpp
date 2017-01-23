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
ll phi[maxn];
void euler_table()
{
    phi[0]=0;phi[1]=1;
    for(int i=2;i<maxn;++i) phi[i]=i;
    for(int i=2;i<maxn;++i)
    {
        if(phi[i]==i)
        {
            for(int j=i;j<maxn;j+=i)
                phi[j]=phi[j]-phi[j]/i;
        }
    }
    for(int i=2;i<maxn;++i)
        phi[i]+=phi[i-1];
}
int factor[20],tot,N;
ll ans;
void dfs(int pos,ll now,int sign)
{
    ans+=N/now*sign;
    for(int i=pos+1;i<tot;++i)
        dfs(i,now*factor[i],-sign);
}
ll cal(int m,int n)
{
    N=n;tot=0;ans=0;
    int M=sqrt(m+0.5);
    for(int i=2;i<=M;++i)
    {
        if(m%i==0)
        {
            factor[tot++]=i;
            while(m%i==0) m/=i;
        }
    }
    if(m>1) factor[tot++]=m;
    for(int i=0;i<tot;++i)
        dfs(i,factor[i],1);
    return n-ans;
}
ll solve(int c,int d,int k)
{
    if(k==0) return 0;
    c/=k;d/=k;
    if(c>d) swap(c,d);
    ll res=phi[c];
    for(int i=c+1;i<=d;++i)
        res+=cal(i,c);
    return res;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int t,tcase=0,a,b,c,d,k;
    euler_table();
    scanf("%d",&t);
    while(t--)
    {
        tcase++;
        scanf("%d%d%d%d%d",&a,&c,&b,&d,&k);
        printf("Case %d: %I64d\n",tcase,solve(c,d,k));
    }
    return 0;
}
