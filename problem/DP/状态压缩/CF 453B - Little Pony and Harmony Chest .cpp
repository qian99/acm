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
int primes[110],m;
int dp[105][1<<17],msk[110];
int a[110],b[110],px[110][1<<17],py[110][1<<17];
void Init()
{
    m=0;
    for(int i=2;i<=60;++i)
    {
        bool flag=true;
        for(int j=2;j<i;++j)
            if(i%j==0) flag=false;
        if(flag) primes[m++]=i;
    }
    for(int i=1;i<=60;++i)
    {
        msk[i]=0;
        for(int j=0;j<m;++j)
            if(i%primes[j]==0) msk[i]|=(1<<j);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    Init();
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    memset(dp,0x3f,sizeof(dp));
    dp[0][0]=0;
    for(int i=0;i<n;++i)
        for(int j=0;j<(1<<m);++j)
        {
            if(dp[i][j]==inf) continue;
            for(int k=1;k<60;++k)
            {
                if(!(j&msk[k]))
                {
                    int v=k-a[i+1];
                    if(v<0) v=-v;
                    if(dp[i+1][j|msk[k]]>dp[i][j]+v)
                    {
                        dp[i+1][j|msk[k]]=dp[i][j]+v;
                        px[i+1][j|msk[k]]=j;
                        py[i+1][j|msk[k]]=k;
                    }
                }
            }
        }
    int minv=inf,p;
    for(int i=0;i<(1<<m);++i)
        if(dp[n][i]<minv) {minv=dp[n][i];p=i;}
    b[n]=py[n][p];
    for(int i=n-1;i>=1;--i)
    {
        p=px[i+1][p];
        b[i]=py[i][p];
    }
    for(int i=1;i<=n;++i)
    {
        if(i>1) printf(" ");
        printf("%d",b[i]);
    }
    printf("\n");
    return 0;
}

