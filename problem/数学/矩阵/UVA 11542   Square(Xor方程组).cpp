#include <iostream>
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
const int maxn=500+10;
bool flag[maxn];
int primes[maxn],pcnt;
void getprimes()
{
    memset(flag,0,sizeof(flag));
    pcnt=0;
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
int A[maxn][maxn];
int solve(int n,int m)
{
    int i=0,j=0,k,u;
    while(i<n&&j<m)
    {
        for(u=i;u<n;++u)
            if(A[u][j]) {break;}
        if(u==n)
        {
            j++;
            continue;
        }
        if(i!=u)
            for(int k=j;k<m;++k) swap(A[i][k],A[u][k]);
        for(u=i+1;u<n;++u)
        {
            if(A[u][j])
            {
                for(k=j;k<m;++k)
                    A[u][k]^=A[i][k];
            }
        }
        i++;
    }
    return i;
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    getprimes();
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        memset(A,0,sizeof(A));
        int maxp=0;
        ll x;
        for(int i=0;i<n;++i)
        {
            scanf("%lld",&x);
            for(int j=0;j<pcnt;++j)
                while(x%primes[j]==0)
                {
                    maxp=max(maxp,j);
                    x/=primes[j];
                    A[j][i]^=1;
                }
        }
        int v=solve(maxp+1,n);
        x=(1LL)<<(n-v);
        printf("%lld\n",x-1);
    }
    return 0;
}
